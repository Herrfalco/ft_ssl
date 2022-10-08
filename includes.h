/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:36:40 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/08 16:31:49 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define BUFF_SZ			256
#define BLOCK_SZ		64
#define BIG_BLOCK_SZ	128
#define BIG_RND_NB		80

typedef __uint128_t	uint128_t;

typedef enum		byte_sz_e {
	BS_16 = 16,
	BS_32 = 32,
	BS_64 = 64,
	BS_128 = 128,
}					byte_sz_t;

typedef struct		md5_s {
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}					md5_t;

typedef struct		sha256_s {
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}					sha256_t;

typedef sha256_t	sha224_t;

typedef struct		sha512_s {
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
}					sha512_t;

typedef sha512_t	sha384_t;

typedef enum		rot_e {
	LEFT,
	RIGHT,
}					rot_t;

void			reverse(void *val, byte_sz_t bs);
uint32_t		rot_32(uint32_t val, uint16_t n, rot_t typ);
uint64_t		rot_64(uint64_t val, uint16_t n, rot_t typ);

char		*md5_result(md5_t *md5);
md5_t		*md5_new(void);
int			md5_mem(md5_t *md5, uint8_t *mem, uint64_t size);

char		*sha256_result(sha256_t *sha256);
sha256_t	*sha256_new(void);
int			sha256_mem(sha256_t *sha256, uint8_t *mem, uint64_t size);

char		*sha224_result(sha224_t *sha224);
sha224_t	*sha224_new(void);
int			sha224_mem(sha224_t *sha224, uint8_t *mem, uint64_t size);

char		*sha512_result(sha512_t *sha512);
sha512_t	*sha512_new(void);
int			sha512_mem(sha512_t *sha512, uint8_t *mem, uint128_t size);

char		*sha384_result(sha384_t *sha384);
sha384_t	*sha384_new(void);
int			sha384_mem(sha384_t *sha384, uint8_t *mem, uint128_t size);

#endif // INCLUDES_H
