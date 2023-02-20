/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:45:11 by fcadet            #+#    #+#             */
/*   Updated: 2023/02/20 11:04:06 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

#include "types.h"
#include <math.h>
#include <fcntl.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <sys/wait.h>

#define TEST_MAX_SZ		(uint64_t)pow(2, 14)

typedef enum		ret_e {
	RT_OK,
	RT_KO,
	RT_RND_GEN,
	RT_MEM_FILE,
	RT_FORK,
	RT_EXIT,
}					ret_t;

typedef uint8_t		rets_t;

typedef uint16_t	(*hash_macro_t)(uint8_t *, uint64_t, uint8_t *);
typedef char		*(*mem_test_t)(uint8_t *, uint64_t sz);
typedef char		*(*file_test_t)(FILE *file);

char				*expect_hash(alg_t alg, uint8_t *str, uint64_t sz);
char				*sha384_mem_test(uint8_t *str, uint64_t sz);
char				*sha512_mem_test(uint8_t *str, uint64_t sz);

#endif	// TEST_H
