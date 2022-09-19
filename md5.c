/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:29:22 by herrfalco         #+#    #+#             */
/*   Updated: 2022/09/19 23:04:47 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFF_SZ		128
#define BLOCK_SZ	64

const uint32_t	keys[] = {	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
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
const uint8_t	rot[] = {	7, 12, 17, 22, 5, 9, 14, 20, 4, 11, 16, 23, 6, 10, 15, 21 };

typedef struct		md5_s {
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}					md5_t;

uint32_t		to_le_32(uint32_t val) {
	return ((val << 24) | (val >> 24) | ((val >> 8) & 0xff00) | ((val << 8) & 0xff0000));
}

char		*md5_result(md5_t *md5) {
	static char		buff[BUFF_SZ];

	sprintf(buff, "%08x%08x%08x%08x",
			to_le_32(md5->a), to_le_32(md5->b), to_le_32(md5->c), to_le_32(md5->d));
	return (buff);
}

md5_t		*md5_new(void) {
	static md5_t	new;

	new.a = to_le_32(0x01234567);
	new.b = to_le_32(0x89abcdef);
	new.c = to_le_32(0xfedcba98);
	new.d = to_le_32(0x76543210);
	return (&new);
}

void		md5_block(md5_t *md5, uint32_t *block) {
	uint8_t			i;
	uint32_t		new_a, n;
	md5_t			md5_sav = *md5;

	for (i = 0; i < BLOCK_SZ; ++i) {
		new_a = md5->a;
		n = rot[(i / 16 * 4) + (i % 4)];
		switch (i / 16) {
			case 0:
				new_a += ((md5->b & md5->c) | ((~md5->b) & md5->d)) + block[i];
				break;
			case 1:
				new_a += ((md5->b & md5->d) | (md5->c & (~md5->d))) + block[(i * 5 + 1) % 16];
				break;
			case 2:
				new_a += (md5->b ^ md5->c ^ md5->d) + block[(i * 3 + 5) % 16];
				break;
			default:
				new_a += (md5->c ^ (md5->b | (~md5->d))) + block[(i * 7) % 16];
		}
		new_a += keys[i];
		new_a = ((new_a << n) | (new_a >> (32 - n))) + md5->b;

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

void		md5_mem(md5_t *md5, uint8_t *mem, uint64_t size) {
	uint8_t		last_block[BLOCK_SZ] = { 0 };
	uint64_t	saved_sz = size;

	for (; size >= BLOCK_SZ; mem += BLOCK_SZ, size -= BLOCK_SZ)
		md5_block(md5, (uint32_t *)mem);
	memcpy(last_block, mem, size);
	last_block[size] = 0x80;
	*(uint64_t *)(last_block + (BLOCK_SZ - 8)) = saved_sz * 8;
	md5_block(md5, (uint32_t *)&last_block);
}

int		main(int argc, char **argv) {
	md5_t		*md5 = md5_new();

	md5_mem(md5, (uint8_t *)argv[1], strlen(argv[1]));
	printf("%s\n", md5_result(md5));
	return (0);
}
