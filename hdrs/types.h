/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:50:33 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/09 18:08:04 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#include "includes.h"

typedef enum		err_e {
	E_NO_ERR,
	E_UNK_ALG,
	E_DUP_OPT,
	E_NO_STR,
	E_HASH_STDIN,
	E_HASH_MEM,
	E_HASH_FILE,
	E_IO,
	E_UNS_OPT,
}					err_t;

typedef uint8_t		errs_t;

typedef __uint128_t	uint128_t;

typedef enum		alg_e {
	A_MD5,
	A_SHA224,
	A_SHA256,
	A_SHA384,
	A_SHA512,
	A_BASE64,
}					alg_t;

typedef uint16_t	opts_t;

typedef enum		opt_e {
	O_PRINT,
	O_QUIET,
	O_REV,
	O_STR,
	O_DEC,
	O_ENC,
	O_IN,
	O_OUT,
	O_NO_OPT,
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

#endif // TYPES_H
