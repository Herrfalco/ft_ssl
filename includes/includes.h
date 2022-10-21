/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:36:40 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/21 10:47:09 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define PAGE_SZ			4096
#define BUFF_SZ			256
#define BLOCK_SZ		64
#define BIG_BLOCK_SZ	128
#define BIG_RND_NB		80
#define	OPT_NB			4
#define ALG_NB			5

typedef enum		err_e {
	E_NO_ERR,
	E_UNK_ALG,
	E_DUP_OPT,
	E_NO_STR,
	E_HASH_STDIN,
	E_HASH_MEM,
	E_HASH_FILE,
}					err_t;

typedef uint8_t		errs_t;

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

char			*to_upper(const char *str);
void			reverse(void *val, byte_sz_t bs);
uint32_t		rot_32(uint32_t val, uint16_t n, rot_t typ);
uint64_t		rot_64(uint64_t val, uint16_t n, rot_t typ);

int				hash_mem_32(vals_32_t *vals, uint8_t *mem, uint64_t sz, proc_block_32_t proc_block, proc_last_block_32_t proc_last_block);
int				hash_file_32(vals_32_t *vals, FILE *file, proc_block_32_t proc_block, proc_last_block_32_t proc_last_block);
int				hash_mem_64(vals_64_t *vals, uint8_t *mem, uint128_t sz, proc_block_64_t proc_block, proc_last_block_64_t proc_last_block);
int				hash_file_64(vals_64_t *vals, FILE *file, proc_block_64_t proc_block, proc_last_block_64_t proc_last_block);

char			*md5_mem(uint8_t *mem, uint64_t size);
char			*md5_file(FILE *file);

char			*sha256_mem(uint8_t *mem, uint64_t size);
char			*sha256_file(FILE *file);

char			*sha224_mem(uint8_t *mem, uint64_t size);
char			*sha224_file(FILE *file);

char			*sha512_mem(uint8_t *mem, uint128_t size);
char			*sha512_file(FILE *file);

char			*sha384_mem(uint8_t *mem, uint128_t size);
char			*sha384_file(FILE *file);

#endif // INCLUDES_H
