/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:39:37 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/09 18:10:36 by fcadet           ###   ########.fr       */
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

opt_t	get_uns_opt(alg_t alg, opts_t opts) {
	uint8_t		i, start = 0, end = O_DEC;

	if (alg < A_BASE64) {
		start = end;
		end = O_NO_OPT;
	}
	for (i = start; i < end; ++i)
		if (opt_isset(opts, i))
			return (i);
	return (O_NO_OPT);
}
