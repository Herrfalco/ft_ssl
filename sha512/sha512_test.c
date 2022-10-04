/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 12:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/03 19:40:42 by fcadet           ###   ########.fr       */
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
	printf("%s\n", result);
	return (result);
}

char		*sha512_cust(uint8_t *str, uint64_t sz) {
	sha512_t		*sha512 = sha512_new();

	sha512_mem(sha512, str, sz);
	printf("%s\n", sha512_result(sha512));
	return (sha512_result(sha512));
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
		if (strcmp(sha512_test(mem, sz), sha512_cust(mem, sz))) {
			fprintf(stderr, "%s%lu%s\n",
					"SHA512 with ", sz, " byte(s): KO");
			free(mem);
			return (2);
		}
	}
	printf("SHA512 with up to %lu byte(s): OK\n", MEM_SZ);
	free(mem);
	return (0);
}
