/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:02:56 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/04 20:08:06 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

uint32_t		swap_end_32(uint32_t val) {
	return ((val << 24) | (val >> 24)
			| ((val >> 8) & 0xff00)
			| ((val << 8) & 0xff0000));
}

void			swap_end(void *val, byte_sz_t byte_sz) {
	uint8_t			tmp[16], i;
	uint64_t		sz = byte_sz / 8;
	
	for (i = 0; i < sz; ++i)
		tmp[sz - 1 - i] = ((uint8_t *)val)[i];
	memcpy(val, &tmp, sz);
}

uint32_t		rot_32(uint32_t val, uint8_t n, rot_t typ) {
	return (typ == LEFT ? (val << n) | (val >> (32 - n))
			: (val >> n) | (val << (32 - n)));
}

uint64_t		rot_64(uint64_t val, uint8_t n, rot_t typ) {
	return (typ == LEFT ? (val << n) | (val >> (64 - n))
			: (val >> n) | (val << (64 - n)));
}
