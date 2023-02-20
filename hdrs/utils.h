/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:59:35 by fcadet            #+#    #+#             */
/*   Updated: 2023/02/20 11:14:36 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
#define UTILS_H

#include "types.h"
#include "defines.h"

extern const char		*ALG_STR[ALG_NB];

uint8_t					ret_2_flag(uint8_t ret);
char					*to_upper(const char *str);
void					reverse(void *val, byte_sz_t bs);
uint32_t				rot_32(uint32_t val, uint16_t n, rot_t typ);
uint64_t				rot_64(uint64_t val, uint16_t n, rot_t typ);

#endif // UTILS_H
