/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:35:49 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/14 15:31:47 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_includes.h"

char		*md5_exp_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[MD5_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    MD5((const unsigned char *)str, sz, buff);
    for (i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

char		*md5_mem_test(uint8_t *str, uint64_t sz) {
	md5_t		*md5 = md5_new();

	md5_mem(md5, str, sz);
	return (md5_result(md5));
}

char		*md5_file_test(FILE *file) {
	md5_t		*md5 = md5_new();

	md5_file(md5, file);
	return (md5_result(md5));
}

int			main(int argc, char **argv) {
	return (run_tests(argc, argv, md5_exp_test, md5_mem_test, md5_file_test));
}
