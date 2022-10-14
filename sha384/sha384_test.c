/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/14 16:39:29 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_includes.h"

char		*sha384_exp_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[SHA384_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    SHA384((const unsigned char *)str, sz, buff);
    for (i = 0; i < SHA384_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

char		*sha384_mem_test(uint8_t *str, uint64_t sz) {
	sha384_t		*sha384 = sha384_new();

	sha384_mem(sha384, str, sz);
	return (sha384_result(sha384));
}

char		*sha384_file_test(FILE *file) {
	sha384_t		*sha384 = sha384_new();

	sha384_file(sha384, file);
	return (sha384_result(sha384));
}

int			main(int argc, char **argv) {
	return (run_tests(argc, argv, sha384_exp_test, sha384_mem_test, sha384_file_test));
}
