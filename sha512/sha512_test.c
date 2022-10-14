/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/14 16:41:16 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_includes.h"

char		*sha512_exp_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[SHA512_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    SHA512((const unsigned char *)str, sz, buff);
    for (i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

char		*sha512_mem_test(uint8_t *str, uint64_t sz) {
	sha512_t		*sha512 = sha512_new();

	sha512_mem(sha512, str, sz);
	return (sha512_result(sha512));
}

char		*sha512_file_test(FILE *file) {
	sha512_t		*sha512 = sha512_new();

	sha512_file(sha512, file);
	return (sha512_result(sha512));
}

int			main(int argc, char **argv) {
	return (run_tests(argc, argv, sha512_exp_test, sha512_mem_test, sha512_file_test));
}
