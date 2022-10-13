/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:52:32 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/10 10:25:15 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static const char			*ERR_STR[] = {
	"No algorithm is given",
	"Unknown algorithm \"%s\"",
	"Duplicated option \"%s\"",
};

static const char			*ALG_STR[] = {
	"md5",
	"sha224",
	"sha256",
	"sha384",
	"sha512" };
static const char			*OPT_STR[] = {
	"-p",
	"-q",
	"-r",
	"-s" };

int		error(err_t err, ...) {
	static char		buff[BUFF_SZ];
	va_list			datas;

	va_start(datas, err);
	vsnprintf(buff, BUFF_SZ, ERR_STR[err], datas);
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

static int			opt_isset(uint8_t *opts, opt_t opt) {
	return (*opts & (0x1 << opt));
}

char	*parse_opts(opts_t *opts, int *argc, char ***argv) {
	int				i, is_opt = 1;

	*opts = 0;
	for (; *argc; --(*argc), ++(*argv)) {
		for (i = 0, is_opt = 0; i < OPT_NB; ++i) {
			if ((is_opt = !strcmp(OPT_STR[i], **argv))) {
				if (opt_isset(opts, i))
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

int			main(int argc, char **argv) {
	opts_t		opts;
	alg_t		alg;
	char		*unk_alg, *dup_opt;

	if (argc < 2)
		return (error(E_NO_ALG));
	--argc;
	++argv;
	if ((unk_alg = parse_alg(&alg, &argc, &argv)))
		return (error(E_UNK_ALG, unk_alg));
	if ((dup_opt = parse_opts(&opts, &argc, &argv)))
		return (error(E_DUP_OPT, dup_opt));

	printf("%s\n", ALG_STR[alg]);

	for (int i = 0; i < OPT_NB; ++i)
		if (opt_isset(&opts, i))
			printf("%s option is set\n", OPT_STR[i]);

	if (argc)
		printf("next arg is \"%s\"\n", *argv);
	return (0);
}
