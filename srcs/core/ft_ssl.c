/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:52:32 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/09 18:23:38 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/core.h"
#include "../../hdrs/utils.h"

static uint8_t			*stdin_2_mem(uint128_t *sz) {
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

static err_t		proc_stdin(alg_t alg, opts_t opts, int argc) {
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

static err_t		proc_str(alg_t alg, opts_t opts, int *argc, char ***argv) {
	char		*hash;

	if (opt_isset(opts, O_STR)) {
		if (!*argc)
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

static err_t		proc_files(alg_t alg, opts_t opts, int *argc, char ***argv) {
	FILE		*file;
	char		*hash;
	err_t		err = E_NO_ERR;

	for (; *argc; --*argc, ++*argv) {
		if (!(file = fopen(**argv, "r"))
			|| !(hash = hash_file(alg, file))) {
			err = error(E_HASH_FILE, **argv);
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
	return (err);
}

int			main(int argc, char **argv) {
	opts_t		opts = 0;
	alg_t		alg;
	char		*unk_alg, *dup_opt;
	errs_t		err = E_NO_ERR;

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
