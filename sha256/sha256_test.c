/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/11 11:30:36 by fcadet           ###   ########.fr       */
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


char		*sha256_exp_test(uint8_t *str, uint64_t sz) {
    uint8_t			buff[SHA256_DIGEST_LENGTH] = { 0 };
	static char		result[BUFF_SZ] = { 0 };
    uint8_t			i;

    SHA256((const unsigned char *)str, sz, buff);
    for (i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(result + 2 * i, "%02x", buff[i]);
	}
	return (result);
}

char		*sha256_mem_test(uint8_t *str, uint64_t sz) {
	sha256_t		*sha256 = sha256_new();

	sha256_mem(sha256, str, sz);
	return (sha256_result(sha256));
}

char		*sha256_file_test(FILE *file) {
	sha256_t		*sha256 = sha256_new();

	sha256_file(sha256, file);
	return (sha256_result(sha256));
}

int			main(int argc, char **argv) {
	int			fd;
	FILE		*file;
	uint64_t	mem_sz = MEM_SZ, sz;
	uint8_t		*mem = NULL;
	ssize_t		read_ret;
	char		*expect;

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
		expect = sha256_exp_test(mem, sz);
		if (!(file = fmemopen(mem, sz, "r"))) {
			fprintf(stderr, "Error: Can't create test file\n");
			free(mem);
			return (2);
		}
		if (strcmp(expect, sha256_mem_test(mem, sz))
				|| strcmp(expect, sha256_file_test(file))) {
			fprintf(stderr, "SHA256 with %lu byte(s): KO\n", sz);
			free(mem);
			return (3);
		}
	}
	printf("SHA256 with up to %lu byte(s): OK\n", mem_sz);
	free(mem);
	return (0);
}
