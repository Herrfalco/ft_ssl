/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:01:53 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:44:34 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/tests.h"
#include "../hdrs/defines.h"

static uint16_t		md5_macro(uint8_t *str, uint64_t sz, uint8_t *buff) {
    MD5((const unsigned char *)str, sz, buff);
	return (MD5_DIGEST_LENGTH);
}

static uint16_t		sha224_macro(uint8_t *str, uint64_t sz, uint8_t *buff) {
    SHA224((const unsigned char *)str, sz, buff);
	return (SHA224_DIGEST_LENGTH);
}

static uint16_t		sha256_macro(uint8_t *str, uint64_t sz, uint8_t *buff) {
    SHA256((const unsigned char *)str, sz, buff);
	return (SHA256_DIGEST_LENGTH);
}

static uint16_t		sha384_macro(uint8_t *str, uint64_t sz, uint8_t *buff) {
    SHA384((const unsigned char *)str, sz, buff);
	return (SHA384_DIGEST_LENGTH);
}

static uint16_t		sha512_macro(uint8_t *str, uint64_t sz, uint8_t *buff) {
    SHA512((const unsigned char *)str, sz, buff);
	return (SHA512_DIGEST_LENGTH);
}

char				*expect_hash(alg_t alg, uint8_t *str, uint64_t sz) {
    uint8_t			buff[SHA512_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint16_t		i, digest_sz;
	hash_macro_t	macros[ALG_NB] = {
		md5_macro,
		sha224_macro,
		sha256_macro,
		sha384_macro,
		sha512_macro,
	};

	digest_sz = macros[alg](str, sz, buff);
    for (i = 0; i < digest_sz; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}
