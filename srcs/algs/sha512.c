/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:36:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/08 07:14:44 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/utils.h"
#include "../../hdrs/common.h"

static const uint64_t		keys[] = {	
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };

static char		*sha512_result(sha512_t *sha512) {
	static char		buff[BUFF_SZ];

	sprintf(buff, "%016llx%016llx%016llx%016llx%016llx%016llx%016llx%016llx",
			sha512->a, sha512->b, sha512->c, sha512->d,
			sha512->e, sha512->f, sha512->g, sha512->h);
	return (buff);
}

static sha512_t	*sha512_new(void) {
	static sha512_t		new;

	new.a = 0x6a09e667f3bcc908;
    new.b = 0xbb67ae8584caa73b;
    new.c = 0x3c6ef372fe94f82b;
    new.d = 0xa54ff53a5f1d36f1;
    new.e = 0x510e527fade682d1;
    new.f = 0x9b05688c2b3e6c1f;
    new.g = 0x1f83d9abfb41bd6b;
    new.h = 0x5be0cd19137e2179;
	return (&new);
}

static uint64_t	*sha512_get_words(uint64_t *block) {
	static uint64_t		words[BIG_BLOCK_SZ];
	uint8_t				i;

	for (i = 0; i < BIG_RND_NB; ++i) {
		if (i < 16) {
			words[i] = block[i];
			reverse(words + i, BS_64);
		} else
			words[i] = (rot_64(words[i - 2], 19, RIGHT)
					^ rot_64(words[i - 2], 61, RIGHT)
					^ (words[i - 2] >> 6))
				+ words[i - 7]
				+ (rot_64(words[i - 15], 1, RIGHT)
					^ rot_64(words[i - 15], 8, RIGHT)
					^ (words[i - 15] >> 7))
				+ words[i - 16];
	}
	return (words);
}

void		sha512_proc_block(sha512_t *sha512, uint64_t *block) {
	uint64_t		i;
	uint64_t		new_a;
	uint64_t		*words = sha512_get_words(block);
	sha512_t		sha512_sav = *sha512;

	for (i = 0; i < BIG_RND_NB; ++i) {
		new_a = words[i] + keys[i] + sha512->h
			+ ((sha512->e & sha512->f) ^ ((~sha512->e) & sha512->g))
			+ (rot_64(sha512->e, 14, RIGHT)
				^ rot_64(sha512->e, 18, RIGHT)
				^ rot_64(sha512->e, 41, RIGHT));
		sha512->d += new_a;
		new_a += ((sha512->a & sha512->b)
				^ (sha512->a & sha512->c)
				^ (sha512->b & sha512->c))
			+ (rot_64(sha512->a, 28, RIGHT)
				^ rot_64(sha512->a, 34, RIGHT)
				^ rot_64(sha512->a, 39, RIGHT));

		sha512->h = sha512->g;
		sha512->g = sha512->f;
		sha512->f = sha512->e;
		sha512->e = sha512->d;
		sha512->d = sha512->c;
		sha512->c = sha512->b;
		sha512->b = sha512->a;
		sha512->a = new_a;
	}
	sha512->a += sha512_sav.a;
	sha512->b += sha512_sav.b;
	sha512->c += sha512_sav.c;
	sha512->d += sha512_sav.d;
	sha512->e += sha512_sav.e;
	sha512->f += sha512_sav.f;
	sha512->g += sha512_sav.g;
	sha512->h += sha512_sav.h;
}

void		sha512_proc_last_block(sha512_t *sha512, uint8_t *block_buff, uint128_t sav_sz, uint128_t rem_sz) {
	block_buff[rem_sz] = 0x80;
	if (BIG_BLOCK_SZ - (rem_sz + 1) < 16) {
		sha512_proc_block(sha512, (uint64_t *)block_buff);
		bzero(block_buff, BIG_BLOCK_SZ);
	}
	reverse(&sav_sz, BS_128);
	*(uint128_t *)(block_buff + BIG_BLOCK_SZ - 16) = sav_sz;
	sha512_proc_block(sha512, (uint64_t *)block_buff);
}

char		*sha512_mem(uint8_t *mem, uint128_t sz) {
	sha512_t	*sha512 = sha512_new();

	return (hash_mem_64(sha512, mem, sz, sha512_proc_block, sha512_proc_last_block) ? NULL : sha512_result(sha512));
}

char		*sha512_file(FILE *file) {
	sha512_t	*sha512 = sha512_new();

	return (hash_file_64(sha512, file, sha512_proc_block, sha512_proc_last_block) ? NULL : sha512_result(sha512));
}
