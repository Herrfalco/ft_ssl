/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:02:56 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/04 20:20:43 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void			reverse(void *val, byte_sz_t bs) {
	uint8_t			tmp[16], i;
	uint64_t		sz = bs / 8;
	
	for (i = 0; i < sz; ++i)
		tmp[sz - 1 - i] = ((uint8_t *)val)[i];
	memcpy(val, &tmp, sz);
}

uint32_t		rot_32(uint32_t val, uint16_t n, rot_t typ) {
	return (typ == LEFT ? (val << n) | (val >> (32 - n))
			: (val >> n) | (val << (32 - n)));
}

uint64_t		rot_64(uint64_t val, uint16_t n, rot_t typ) {
	return (typ == LEFT ? (val << n) | (val >> (64 - n))
			: (val >> n) | (val << (64 - n)));
}
