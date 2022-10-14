/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:35:49 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/14 17:09:19 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/test_includes.h"

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

int			main(int argc, char **argv) {
	return (run_tests(argc, argv, md5_exp_test, md5_mem, md5_file));
}
