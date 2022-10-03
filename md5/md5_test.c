/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:35:49 by herrfalco         #+#    #+#             */
/*   Updated: 2022/09/24 13:14:33 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include "../includes.h"

#include <openssl/md5.h>
#include <stdlib.h>
#include <unistd.h>

#define MEM_SZ		(uint64_t)pow(2, 14)
#define RAND_NB		10

char		*md5_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[MD5_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    MD5((const unsigned char *)str, sz, buff);
    for (i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

char		*md5_cust(uint8_t *str, uint64_t sz) {
	md5_t		*md5 = md5_new();

	md5_mem(md5, str, sz);
	return (md5_result(md5));
}

int			main(void) {
	int			fd;
	uint8_t		*mem = NULL;
	uint64_t	sz;

	if ((fd = open("/dev/random", O_RDONLY)) < 0
			|| !(mem = malloc(MEM_SZ))
			|| read(fd, mem, MEM_SZ) != MEM_SZ) {
		fprintf(stderr, "Error: Can't generate random number\n");
		if (mem)
			free(mem);
		return (1);
	}
	for (sz = 0; sz <= MEM_SZ; ++sz) {
		if (strcmp(md5_test(mem, sz), md5_cust(mem, sz))) {
			fprintf(stderr, "%s%lu%s\n",
					"MD5 with ", sz, " byte(s): KO");
			free(mem);
			return (2);
		}
	}
	printf("MD5 with up to %lu byte(s): OK\n", MEM_SZ);
	free(mem);
	return (0);
}
