/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/14 19:38:49 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/test_includes.h"

static char		*sha256_exp_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[SHA256_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    SHA256((const unsigned char *)str, sz, buff);
    for (i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

int			main(int argc, char **argv) {
	return (run_tests(argc, argv, sha256_exp_test, sha256_mem, sha256_file));
}
