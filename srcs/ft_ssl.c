/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:52:32 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/22 12:03:17 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int		disp_help(void) {
	const char	*help = "ft_ssl ALG [OPTS] [FILES]\n" \
		"	ALG:\n" \
		"		md5\n" \
		"		sha224\n" \
		"		sha256\n" \
		"		sha384\n" \
		"		sha512\n" \
		"	OPTS:\n" \
		"		-p	Echo stdin\n" \
		"		-q	Quiet mode\n" \
		"		-r	Reverse format\n" \
		"		-s	Hash string\n";

	printf("%s", help);
	return (0);
}

err_t	error(err_t err, ...) {
	const char		*err_str[] = {
		"Unknown algorithm \"%s\"",
		"Duplicated option \"%s\"",
		"No string specified",
		"Can't hash stdin",
		"Can't hash memory",
		"Can't hash file \"%s\"",
	};
	char					buff[BUFF_SZ];
	va_list					datas;

	va_start(datas, err);
	vsnprintf(buff, BUFF_SZ, err_str[err - 1], datas);
	va_end(datas);
	fprintf(stderr, "Error: %s\n", buff);
	return (err);
}

char	*parse_alg(alg_t *alg, int *argc, char ***argv) {
		int				i;

		for (i = 0; i < ALG_NB; ++i) {
			if (!strcmp(**argv, ALG_STR[i])) {
				--(*argc);
				++(*argv);
				*alg = i;
				return (NULL);
			}
		}
		return (**argv);
}

static void			opt_set(uint8_t *opts, opt_t opt) {
	*opts |= (0x1 << opt);
}

static int			opt_isset(uint8_t opts, opt_t opt) {
	return (opts & (0x1 << opt));
}

char	*parse_opts(opts_t *opts, int *argc, char ***argv) {
	const char			*OPT_STR[] = {
		"-p",
		"-q",
		"-r",
		"-s" };
	int				i, is_opt = 1;

	*opts = 0;
	for (; *argc; --(*argc), ++(*argv)) {
		for (i = 0, is_opt = 0; i < OPT_NB; ++i) {
			if ((is_opt = !strcmp(OPT_STR[i], **argv))) {
				if (opt_isset(*opts, i))
					return (**argv);
				opt_set(opts, i);
				break;
			}
		}
		if (!is_opt)
			break;
	}
	return (NULL);
}

char		*hash_mem(alg_t alg, uint8_t *mem, uint128_t sz) {
	switch (alg) {
		case A_MD5:
			return (md5_mem(mem, sz));
		case A_SHA224:
			return (sha224_mem(mem, sz));
		case A_SHA256:
			return (sha256_mem(mem, sz));
		case A_SHA384:
			return (sha384_mem(mem, sz));
		case A_SHA512:
			return (sha512_mem(mem, sz));
		default:
			return (NULL);
	}
}

char		*hash_file(alg_t alg, FILE *file) {
	switch (alg) {
		case A_MD5:
			return (md5_file(file));
		case A_SHA224:
			return (sha224_file(file));
		case A_SHA256:
			return (sha256_file(file));
		case A_SHA384:
			return (sha384_file(file));
		case A_SHA512:
			return (sha512_file(file));
		default:
			return (NULL);
	}
}

uint8_t			*stdin_2_mem(uint128_t *sz) {
	ssize_t				read_ret = 0;
	uint8_t				*old_mem = NULL;
	static uint8_t		*mem;

	for (mem = malloc(PAGE_SZ), *sz = 0;
			mem && (read_ret = read(0, mem + *sz, PAGE_SZ)) == PAGE_SZ;
			*sz += PAGE_SZ, old_mem = mem, mem = realloc(mem, *sz + PAGE_SZ));
	if (!mem && old_mem)
		free(old_mem);
	else if (read_ret < 0) {
		free(mem);
		mem = NULL;
	}
	*sz += read_ret;
	return (mem);
}

err_t		proc_stdin(alg_t alg, opts_t opts, int argc) {
	char		*hash;
	uint8_t		*stdin_mem;
	uint128_t	mem_sz;

	if (opt_isset(opts, O_PRINT)) {
		if (!(stdin_mem = stdin_2_mem(&mem_sz)))
			return (error(E_HASH_STDIN));
		if (!(hash = hash_mem(alg, stdin_mem, mem_sz))) {
			free(stdin_mem);
			return (error(E_HASH_STDIN));
		}
		if (opt_isset(opts, O_QUIET))
			printf("%.*s%s\n", (int)mem_sz, stdin_mem, hash);
		else {
			for (; mem_sz && stdin_mem[mem_sz - 1] == '\n'; --mem_sz);
			printf("(\"%.*s\") = %s\n", (int)mem_sz, stdin_mem, hash);
		}
		free(stdin_mem);
	} else if (!opt_isset(opts, O_STR) && !argc) {
		if (!(hash = hash_file(alg, stdin)))
			return (error(E_HASH_STDIN));
		if (opt_isset(opts, O_QUIET))
			printf("%s\n", hash);
		else
			printf("(stdin) = %s\n", hash);
	}
	return (E_NO_ERR);
}

err_t		proc_str(alg_t alg, opts_t opts, int *argc, char ***argv) {
	char		*hash;

	if (opt_isset(opts, O_STR)) {
		if (!argc)
			return (error(E_NO_STR));
		if (!(hash = hash_mem(alg, (uint8_t *)**argv, strlen(**argv))))
			return (error(E_HASH_MEM));
		if (opt_isset(opts, O_QUIET))
			printf("%s\n", hash);
		else {
			if (opt_isset(opts, O_REV))
				printf("%s \"%s\"\n", hash, **argv);
			else
				printf("%s (\"%s\") = %s\n",
						to_upper(ALG_STR[alg]), **argv, hash);
		}
		--*argc;
		++*argv;
	}
	return (E_NO_ERR);
}

err_t		proc_files(alg_t alg, opts_t opts, int *argc, char ***argv) {
	FILE		*file;
	char		*hash;
	err_t		err = 0;

	for (; *argc; --*argc, ++*argv) {
		if (!(file = fopen(**argv, "r"))
			|| !(hash = hash_file(alg, file))) {
			err |= error(E_HASH_FILE, **argv);
			if (file)
				fclose(file);
			continue;
		}
		fclose(file);
		if (opt_isset(opts, O_QUIET))
			printf("%s\n", hash);
		else if (opt_isset(opts, O_REV))
			printf("%s %s\n", hash, **argv);
		else
			printf("%s (%s) = %s\n",
					to_upper(ALG_STR[alg]), **argv, hash);
	}
	return (E_NO_ERR);
}

int			main(int argc, char **argv) {
	opts_t		opts = 0;
	alg_t		alg;
	char		*unk_alg, *dup_opt;
	errs_t		err = 0;

	if (argc < 2)
		return (disp_help());
	--argc;
	++argv;
	if ((unk_alg = parse_alg(&alg, &argc, &argv)))
		return (error(E_UNK_ALG, unk_alg));
	if ((dup_opt = parse_opts(&opts, &argc, &argv)))
		return (error(E_DUP_OPT, dup_opt));
	err |= ret_2_flag(proc_stdin(alg, opts, argc));
	err |= ret_2_flag(proc_str(alg, opts, &argc, &argv));
	err |= ret_2_flag(proc_files(alg, opts, &argc, &argv));
	return (err);
}
