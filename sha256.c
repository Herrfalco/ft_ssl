/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:36:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/09/24 12:11:30 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

const uint32_t		keys[] = {	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
								0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
								0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
								0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
								0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
								0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
								0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
								0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
								0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
								0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
								0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
								0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
								0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
								0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
								0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
								0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2 };

char		*sha256_result(sha256_t *sha256) {
	static char		buff[BUFF_SZ];

	sprintf(buff, "%08x%08x%08x%08x%08x%08x%08x%08x",
			sha256->a, sha256->b, sha256->c, sha256->d,
			sha256->e, sha256->f, sha256->g, sha256->h);
	return (buff);
}

sha256_t	*sha256_new(void) {
	static sha256_t		new;

	new.a = 0x6a09e667;
	new.b = 0xbb67ae85;
	new.c = 0x3c6ef372;
	new.d = 0xa54ff53a;
	new.e = 0x510e527f;
	new.f = 0x9b05688c;
	new.g = 0x1f83d9ab;
	new.h = 0x5be0cd19;
	return (&new);
}

static uint32_t	*sha256_get_words(uint32_t *block) {
	static uint32_t		words[BLOCK_SZ];
	uint8_t				i;

	for (i = 0; i < BLOCK_SZ; ++i) {
		if (i < 16)
			words[i] = swap_end_32(block[i]);
		else
			words[i] = (rot_32(words[i - 2], 17, RIGHT)
					^ rot_32(words[i - 2], 19, RIGHT)
					^ (words[i - 2] >> 10))
				+ words[i - 7]
				+ (rot_32(words[i - 15], 7, RIGHT)
					^ rot_32(words[i - 15], 18, RIGHT)
					^ (words[i - 15] >> 3))
				+ words[i - 16];
	}
	return (words);
}

static void		sha256_proc_block(sha256_t *sha256, uint32_t *block) {
	uint64_t		i;
	uint32_t		new_a;
	uint32_t		*words = sha256_get_words(block);
	sha256_t		sha256_sav = *sha256;

	for (i = 0; i < BLOCK_SZ; ++i) {
		new_a = words[i] + keys[i] + sha256->h
			+ ((sha256->e & sha256->f) ^ ((~sha256->e) & sha256->g))
			+ (rot_32(sha256->e, 6, RIGHT)
				^ rot_32(sha256->e, 11, RIGHT)
				^ rot_32(sha256->e, 25, RIGHT));
		sha256->d += new_a;
		new_a += ((sha256->a & sha256->b)
				^ (sha256->a & sha256->c)
				^ (sha256->b & sha256->c))
			+ (rot_32(sha256->a, 2, RIGHT)
				^ rot_32(sha256->a, 13, RIGHT)
				^ rot_32(sha256->a, 22, RIGHT));

		sha256->h = sha256->g;
		sha256->g = sha256->f;
		sha256->f = sha256->e;
		sha256->e = sha256->d;
		sha256->d = sha256->c;
		sha256->c = sha256->b;
		sha256->b = sha256->a;
		sha256->a = new_a;
	}
	sha256->a += sha256_sav.a;
	sha256->b += sha256_sav.b;
	sha256->c += sha256_sav.c;
	sha256->d += sha256_sav.d;
	sha256->e += sha256_sav.e;
	sha256->f += sha256_sav.f;
	sha256->g += sha256_sav.g;
	sha256->h += sha256_sav.h;
}

void		sha256_mem(sha256_t *sha256, uint8_t *mem, uint64_t size) {
	uint8_t			block_buff[BLOCK_SZ] = { 0 };
	uint64_t		saved_sz = size;

	for (; size >= BLOCK_SZ; mem += BLOCK_SZ,
			size -= size < BLOCK_SZ ? size : BLOCK_SZ)
		sha256_proc_block(sha256, (uint32_t *)mem);
	memcpy(&block_buff, mem, size);
	block_buff[size] = 0x80;
	if (BLOCK_SZ - (size + 1) >= 8)
		*(uint64_t *)(block_buff + BLOCK_SZ - 8)
			= swap_end_64(saved_sz * 8);
	else {
		sha256_proc_block(sha256, (uint32_t *)block_buff);
		bzero(block_buff, BLOCK_SZ);
		*(uint64_t *)(block_buff + BLOCK_SZ - 8)
			= swap_end_64(saved_sz * 8);
	}
	sha256_proc_block(sha256, (uint32_t *)block_buff);
}
