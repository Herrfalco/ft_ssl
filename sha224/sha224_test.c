/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/14 16:04:33 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_includes.h"

char		*sha224_exp_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[SHA224_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    SHA224((const unsigned char *)str, sz, buff);
    for (i = 0; i < SHA224_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

char		*sha224_mem_test(uint8_t *str, uint64_t sz) {
	sha224_t		*sha224 = sha224_new();

	sha224_mem(sha224, str, sz);
	return (sha224_result(sha224));
}

char		*sha224_file_test(FILE *file) {
	sha224_t		*sha224 = sha224_new();

	sha224_file(sha224, file);
	return (sha224_result(sha224));
}

int			main(int argc, char **argv) {
	return (run_tests(argc, argv, sha224_exp_test, sha224_mem_test, sha224_file_test));
}
