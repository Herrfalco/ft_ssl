/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:23:22 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/09 16:53:05 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../hdrs/includes.h"
#include "../../../hdrs/defines.h"
#include "../../../hdrs/types.h"

static char		*b64_conv_block(uint8_t *block, uint8_t sz) {
	uint16_t		buff = 0;
	uint8_t			rem = 0;
	static char		result[5] = { 0 };
	const char		*map = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
							"abcdefghijklmnopqrstuvwxyz" \
							"0123456789+/";
	uint8_t			i;

	for (i = 0; i < 4; ++i, buff <<= 6, rem += 2) {
		if (i < sz)
			buff |= block[i] << (8 - rem);
		result[i] = i > sz ? '=' : map[buff >> 10];
	}
	return (result);
}

err_t			b64_mem(FILE *dst, uint8_t *mem, uint64_t sz) {
	for (; sz; sz = sz < 3 ? 0 : sz - 3, mem += 3)
		if (fwrite(b64_conv_block(mem, sz < 3 ? sz : 3),
				sizeof(char), 4, dst) != 4)
			return (E_IO);
	return (E_NO_ERR);
}

err_t			b64_file(FILE *dst, FILE *src) {
	uint8_t		buff[BUFF_SZ];
	uint64_t	sz;

	while ((sz = fread(buff, sizeof(uint8_t), BUFF_SZ, src)))
		if (ferror(src) || b64_mem(dst, buff, sz))
			return (E_IO);
	return (E_NO_ERR);
}
