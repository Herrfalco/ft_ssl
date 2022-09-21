/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:35:49 by herrfalco         #+#    #+#             */
/*   Updated: 2022/09/21 07:14:54 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include "includes.h"

#include <openssl/md5.h>
#include <string.h>

void md5_hash_from_string (char *string, char *hash)
{
    int i;
    char unsigned md5[MD5_DIGEST_LENGTH] = {0};

    MD5((const unsigned char *)string, strlen(string), md5);

    for (i=0; i < MD5_DIGEST_LENGTH; i++) {
        sprintf(hash + 2*i, "%02x", md5[i]);
    }
}

int			main(void) {
	uint8_t		buff[BLOCK_SZ];
	int			rand_fd = open("/dev/urandom", O_RDONLY);
	uint64_t	i, sz;

	if (rand_fd < 0) {
		fprintf(stderr, "Error: Can't generate random number\n");
		return (1);
	}
	for (i = 1; i <= pow(2, 25); i *= 2) {
		for (sz = i; sz; sz -= sz < 512 ? sz : 512) {
		}
	}
	return (0);
}
