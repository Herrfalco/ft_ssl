/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:39:37 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/08 09:19:05 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/utils.h"

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

static void		opt_set(opts_t *opts, opt_t opt) {
	*opts |= (0x1 << opt);
}

int				opt_isset(opts_t opts, opt_t opt) {
	return (opts & (0x1 << opt));
}

char	*parse_opts(opts_t *opts, int *argc, char ***argv) {
	const char			*OPT_STR[] = {
		"-p",
		"-q",
		"-r",
		"-s",
		"-d",
		"-e",
		"-i",
		"-o",
	};
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
