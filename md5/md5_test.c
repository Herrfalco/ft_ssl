/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:35:49 by herrfalco         #+#    #+#             */
/*   Updated: 2022/10/11 11:12:09 by fcadet           ###   ########.fr       */
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
		fprintf(stderr, "Error: Can't generate random data\n");
		if (mem)
			free(mem);
		return (1);
	}
	for (sz = 0; sz <= mem_sz; ++sz) {
		expect = md5_exp_test(mem, sz);
		if (!(file = fmemopen(mem, sz, "r"))) {
			fprintf(stderr, "Error: Can't create test file\n");
			free(mem);
			return (2);
		}
		if (strcmp(expect, md5_mem_test(mem, sz))
				|| strcmp(expect, md5_file_test(file))) {
			fprintf(stderr, "MD5 with %lu byte(s): KO\n", sz);
			free(mem);
			return (3);
		}
		fclose(file);
	}
	printf("MD5 with up to %lu byte(s): OK\n", mem_sz);
	free(mem);
	return (0);
}
