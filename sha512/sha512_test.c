/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/05 18:28:11 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <fcntl.h>
#include "../includes.h"

#include <openssl/sha.h>
#include <stdlib.h>
#include <unistd.h>

#define MEM_SZ		(uint64_t)pow(2, 14)
#define RAND_NB		10


char		*sha512_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[SHA512_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    SHA512((const unsigned char *)str, sz, buff);
    for (i = 0; i < SHA512_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

char		*sha512_cust(uint8_t *str, uint64_t sz) {
	sha512_t		*sha512 = sha512_new();

	sha512_mem(sha512, str, sz);
	return (sha512_result(sha512));
}

int			main(int argc, char **argv) {
	int			fd;
	uint64_t	mem_sz = MEM_SZ, sz;
	uint8_t		*mem = NULL;
	ssize_t		read_ret;

	if (argc > 1) {
		mem_sz = (uint64_t)strtoll(argv[1], NULL, 10);
		if ((int64_t)mem_sz < 1) {
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
		if (strcmp(sha512_test(mem, sz), sha512_cust(mem, sz))) {
			fprintf(stderr, "SHA512 with %lu byte(s): KO\n", sz);
			free(mem);
			return (2);
		}
	}
	printf("SHA512 with up to %lu byte(s): OK\n", mem_sz);
	free(mem);
	return (0);
}
