/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:52:32 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/09 10:49:22 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

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

char	*parse_opts(opts_t *opts, int *argc, char ***argv) {
	uint8_t			found;
	int				i;

	*opts = 0;
	for (; *argc; --(*argc), ++(*argv)) {
		found = 0;
		for (i = 0; i < OPT_NB; ++i) {
			if (!strcmp(OPT_STR[i], **argv)) {
				if (*opts & (0x1 << i))
					return (**argv);
				*opts |= (0x1 << i);
				found = 1;
				break;
			}
		}
		if (!found)
			return (NULL);
	}
	return (NULL);
}

int			opt_isset(uint8_t *opts, opt_t opt) {
	return (*opts & (0x1 << opt));
}

int			main(int argc, char **argv) {
	opts_t		opts;
	alg_t		alg;
	char		*unk_alg, *dup_opt;

	if (argc < 2) {
		printf("Error: No algorithm selected\n");
		return (-1);
	}
	--argc;
	++argv;
	if ((unk_alg = parse_alg(&alg, &argc, &argv))) {
		printf("Error: Unknown algorithm \"%s\"\n", unk_alg);
		return (-2);
	}
	if ((dup_opt = parse_opts(&opts, &argc, &argv))) {
		printf("Error: Duplicated option \"%s\"\n", dup_opt);
		return (-3);
	}

	printf("%s\n", ALG_STR[alg]);

	for (int i = 0; i < OPT_NB; ++i)
		if (opt_isset(&opts, i))
			printf("%s option is set\n", OPT_STR[i]);

	if (argc)
		printf("next arg is \"%s\"\n", *argv);
	return (0);
}
