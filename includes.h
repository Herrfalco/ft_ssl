/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:36:40 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/11 13:02:52 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

#define BUFF_SZ			256
#define BLOCK_SZ		64
#define BIG_BLOCK_SZ	128
#define BIG_RND_NB		80
#define	OPT_NB			4
#define ALG_NB			5

typedef enum		err_e {
	E_NO_ALG,
	E_UNK_ALG,
	E_DUP_OPT,
}					err_t;

typedef __uint128_t	uint128_t;

typedef enum		alg_e {
	A_MD5,
	A_SHA224,
	A_SHA256,
	A_SHA384,
	A_SHA512,
}					alg_t;

typedef uint8_t		opts_t;

typedef enum		opt_e {
	O_PRINT,
	O_QUIET,
	O_REV,
	O_STR,
}					opt_t;

typedef enum		byte_sz_e {
	BS_16 = 16,
	BS_32 = 32,
	BS_64 = 64,
	BS_128 = 128,
}					byte_sz_t;

typedef struct		vals_32_s {
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}					vals_32_t;

typedef vals_32_t	md5_t;
typedef vals_32_t	sha256_t;
typedef vals_32_t	sha224_t;

typedef struct		vals_64_s {
	uint64_t		a;
	uint64_t		b;
	uint64_t		c;
	uint64_t		d;
	uint64_t		e;
	uint64_t		f;
	uint64_t		g;
	uint64_t		h;
}					vals_64_t;

typedef vals_64_t	sha512_t;
typedef vals_64_t	sha384_t;

typedef enum		rot_e {
	LEFT,
	RIGHT,
}					rot_t;

typedef void	(*proc_block_32_t)(vals_32_t *, uint32_t *);
typedef void	(*proc_last_block_32_t)(vals_32_t *, uint8_t *, uint64_t, uint64_t);
typedef void	(*proc_block_64_t)(vals_64_t *, uint64_t *);
typedef void	(*proc_last_block_64_t)(vals_64_t *, uint8_t *, uint128_t, uint128_t);

void			reverse(void *val, byte_sz_t bs);
uint32_t		rot_32(uint32_t val, uint16_t n, rot_t typ);
uint64_t		rot_64(uint64_t val, uint16_t n, rot_t typ);
int				hash_mem_32(vals_32_t *vals, uint8_t *mem, uint64_t sz, proc_block_32_t proc_block, proc_last_block_32_t proc_last_block);
int				hash_file_32(vals_32_t *vals, FILE *file, proc_block_32_t proc_block, proc_last_block_32_t proc_last_block);
int				hash_mem_64(vals_64_t *vals, uint8_t *mem, uint128_t sz, proc_block_64_t proc_block, proc_last_block_64_t proc_last_block);
int				hash_file_64(vals_64_t *vals, FILE *file, proc_block_64_t proc_block, proc_last_block_64_t proc_last_block);

char		*md5_result(md5_t *md5);
md5_t		*md5_new(void);
int			md5_mem(md5_t *md5, uint8_t *mem, uint64_t size);
int			md5_file(md5_t *md5, FILE *file);

char		*sha256_result(sha256_t *sha256);
sha256_t	*sha256_new(void);
int			sha256_mem(sha256_t *sha256, uint8_t *mem, uint64_t size);
int			sha256_file(sha256_t *sha256, FILE *file);

char		*sha224_result(sha224_t *sha224);
sha224_t	*sha224_new(void);
int			sha224_mem(sha224_t *sha224, uint8_t *mem, uint64_t size);
int			sha224_file(sha224_t *sha224, FILE *file);

char		*sha512_result(sha512_t *sha512);
sha512_t	*sha512_new(void);
int			sha512_mem(sha512_t *sha512, uint8_t *mem, uint128_t size);
int			sha512_file(sha512_t *sha512, FILE *file);

char		*sha384_result(sha384_t *sha384);
sha384_t	*sha384_new(void);
int			sha384_mem(sha384_t *sha384, uint8_t *mem, uint128_t size);
int			sha384_file(sha384_t *sha384, FILE *file);

#endif // INCLUDES_H
