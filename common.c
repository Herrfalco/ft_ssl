/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:02:56 by fcadet            #+#    #+#             */
/*   Updated: 2022/09/24 09:37:54 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

uint32_t		swap_end_32(uint32_t val) {
	return ((val << 24) | (val >> 24)
			| ((val >> 8) & 0xff00)
			| ((val << 8) & 0xff0000));
}

uint64_t		swap_end_64(uint64_t val) {
	uint64_t		result = 0, l_mask, r_mask;
	int8_t			i;

	for (i = 56, l_mask = 0xff00000000000000, r_mask = 0xff;
			i > 0; i -= 16, l_mask >>= 8, r_mask <<= 8) {
		result |= (val >> i) & (l_mask >> i);
		result |= (val << i) & (r_mask << i);
	}
	return (result);
}

uint32_t		rot_32(uint32_t val, uint8_t n, rot_t typ) {
	return (typ == LEFT ? (val << n) | (val >> (32 - n))
			: (val >> n) | (val << (32 - n)));
}
