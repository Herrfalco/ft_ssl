/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:42:15 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:04:24 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
#define CORE_H

#include "types.h"

int		disp_help(void);
err_t	error(err_t err, ...);

char	*hash_mem(alg_t alg, uint8_t *mem, uint128_t sz);
char	*hash_file(alg_t alg, FILE *file);

char	*parse_alg(alg_t *alg, int *argc, char ***argv);
int		opt_isset(uint8_t opts, opt_t opt);
char	*parse_opts(opts_t *opts, int *argc, char ***argv);

#endif // CORE_H
