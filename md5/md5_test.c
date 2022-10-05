/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:35:49 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/05 17:04:30 by fcadet           ###   ########.fr       */
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

int			main(int argc, char **argv) {
	int			fd;
	uint64_t	mem_sz = MEM_SZ, sz;
	uint8_t		*mem = NULL;
	ssize_t		read_ret;

	if (argc > 1) {
		mem_sz = (uint64_t)atoi(argv[1]);
		if ((int)mem_sz < 0) {
			fprintf(stderr, "Error: Invalid parameter\n");
			return (1);
		}
	}
	if ((fd = open("/dev/random", O_RDONLY)) < 0
			|| !(mem = malloc(mem_sz))
			|| (read_ret = read(fd, mem, mem_sz)) < 0
			|| (uint64_t)read_ret != mem_sz) {
		fprintf(stderr, "Error: Can't generate random number\n");
		if (mem)
			free(mem);
		return (1);
	}
	for (sz = 0; sz <= mem_sz; ++sz) {
		if (strcmp(md5_test(mem, sz), md5_cust(mem, sz))) {
			fprintf(stderr, "MD5 with %lu byte(s): KO\n", sz);
			free(mem);
			return (2);
		}
	}
	printf("MD5 with up to %lu byte(s): OK\n", mem_sz);
	free(mem);
	return (0);
}
