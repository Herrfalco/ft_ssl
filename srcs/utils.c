/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 08:02:56 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:21:59 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/types.h"
#include "../hdrs/defines.h"

const char		*ALG_STR[] = {
	"md5",
	"sha224",
	"sha256",
	"sha384",
	"sha512",
};

uint8_t		ret_2_flag(uint8_t ret) {
	return (!!ret << (ret - 1));
}

char			*to_upper(const char *str) {
	static char		buff[BUFF_SZ];
	uint16_t		i;

	for (i = 0; str[i]; ++i)
		buff[i] = str[i] >= 'a' && str[i] <= 'z' ? str[i] - 0x20 : str[i];
	buff[i] = 0;
	return (buff);
}

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
