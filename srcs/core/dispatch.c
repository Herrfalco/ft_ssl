/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:40:42 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:16:44 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/algs.h"

char		*hash_mem(alg_t alg, uint8_t *mem, uint128_t sz) {
	switch (alg) {
		case A_MD5:
			return (md5_mem(mem, sz));
		case A_SHA224:
			return (sha224_mem(mem, sz));
		case A_SHA256:
			return (sha256_mem(mem, sz));
		case A_SHA384:
			return (sha384_mem(mem, sz));
		case A_SHA512:
			return (sha512_mem(mem, sz));
		default:
			return (NULL);
	}
}

char		*hash_file(alg_t alg, FILE *file) {
	switch (alg) {
		case A_MD5:
			return (md5_file(file));
		case A_SHA224:
			return (sha224_file(file));
		case A_SHA256:
			return (sha256_file(file));
		case A_SHA384:
			return (sha384_file(file));
		case A_SHA512:
			return (sha512_file(file));
		default:
			return (NULL);
	}
}
