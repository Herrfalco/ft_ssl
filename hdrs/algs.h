/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:00:52 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:05:30 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGS_H
#define ALGS_H

#include "types.h"

char	*md5_mem(uint8_t *mem, uint64_t size);
char	*md5_file(FILE *file);

char	*sha256_mem(uint8_t *mem, uint64_t size);
char	*sha256_file(FILE *file);

char	*sha224_mem(uint8_t *mem, uint64_t size);
char	*sha224_file(FILE *file);

char	*sha512_mem(uint8_t *mem, uint128_t size);
char	*sha512_file(FILE *file);

char	*sha384_mem(uint8_t *mem, uint128_t size);
char	*sha384_file(FILE *file);

#endif // ALGS_H
