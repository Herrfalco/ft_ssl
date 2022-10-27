/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:29:22 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/27 17:22:49 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/utils.h"
#include "../../hdrs/common.h"

static const uint32_t	keys[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };
static const uint8_t	rot[] = {	7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21 };

static char		*md5_result(md5_t *md5) {
	static char		buff[BUFF_SZ];
	md5_t			sw_md5 = *md5;

	reverse(&sw_md5.a, BS_32);
	reverse(&sw_md5.b, BS_32);
	reverse(&sw_md5.c, BS_32);
	reverse(&sw_md5.d, BS_32);
	sprintf(buff, "%08x%08x%08x%08x", sw_md5.a, sw_md5.b, sw_md5.c, sw_md5.d);
	return (buff);
}

static md5_t	*md5_new(void) {
	static md5_t	new;
	
	new.a = 0x01234567,
	new.b = 0x89abcdef,
	new.c = 0xfedcba98,
	new.d = 0x76543210,

	reverse(&new.a, BS_32);
	reverse(&new.b, BS_32);
	reverse(&new.c, BS_32);
	reverse(&new.d, BS_32);
	return (&new);
}

static void		md5_proc_block(md5_t *md5, uint32_t *block) {
	uint8_t			i;
	uint32_t		new_a, n;
	md5_t			md5_sav = *md5;

	for (i = 0; i < BLOCK_SZ; ++i) {
		new_a = md5->a;
		n = rot[(i / 16 * 4) + (i % 4)];
		switch (i / 16) {
			case 0:
				new_a += ((md5->b & md5->c) | ((~md5->b) & md5->d))
					+ block[i];
				break;
			case 1:
				new_a += ((md5->b & md5->d) | (md5->c & (~md5->d)))
					+ block[(i * 5 + 1) % 16];
				break;
			case 2:
				new_a += (md5->b ^ md5->c ^ md5->d)
					+ block[(i * 3 + 5) % 16];
				break;
			default:
				new_a += (md5->c ^ (md5->b | (~md5->d)))
					+ block[(i * 7) % 16];
		}
		new_a += keys[i];
		new_a = rot_32(new_a, n, LEFT) + md5->b;

		md5->a = md5->d;
		md5->d = md5->c;
		md5->c = md5->b;
		md5->b = new_a;
	}
	md5->a += md5_sav.a;
	md5->b += md5_sav.b;
	md5->c += md5_sav.c;
	md5->d += md5_sav.d;
}

static void	md5_proc_last_block(md5_t *md5, uint8_t *block_buff, uint64_t sav_sz, uint64_t rem_sz) {
	block_buff[rem_sz] = 0x80;
	if (BLOCK_SZ - (rem_sz + 1) < 8) {
		md5_proc_block(md5, (uint32_t *)block_buff);
		bzero(block_buff, BLOCK_SZ);
	}
	*(uint64_t *)(block_buff + BLOCK_SZ - 8) = sav_sz;
	md5_proc_block(md5, (uint32_t *)block_buff);
}

char		*md5_mem(uint8_t *mem, uint64_t sz) {
	md5_t		*md5 = md5_new();

	return (hash_mem_32(md5, mem, sz, md5_proc_block, md5_proc_last_block) ? NULL : md5_result(md5));
}

char		*md5_file(FILE *file) {
	md5_t		*md5 = md5_new();

	return (hash_file_32(md5, file, md5_proc_block, md5_proc_last_block) ? NULL : md5_result(md5));
}
