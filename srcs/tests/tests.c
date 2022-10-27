/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:03:06 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 15:37:02 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_includes.h"

static rets_t	test_ret(ret_t ret, ...) {
	const char			*ret_str[] = {
		"%s with up to %lu byte(s): OK",
		"%s with %lu byte(s): KO",
		"Can't generate random data",
		"Can't create memory file",
		"Can't fork %s test",
		"Unexpected process stop",
	};
	char				buff[BUFF_SZ];
	va_list				datas;

	va_start(datas, ret);
	vsnprintf(buff, BUFF_SZ, ret_str[ret], datas);
	va_end(datas);
	if (ret)
		fprintf(stderr, "Error: %s\n", buff);
	else
		printf("%s\n", buff);
	return (ret_2_flag(ret));
}

static int		rand_mem(uint8_t **mem, uint64_t mem_sz) {
	ssize_t		read_ret;
	int			fd;

	if ((fd = open("/dev/random", O_RDONLY)) < 0
			|| !(*mem = malloc(mem_sz))
			|| (read_ret = read(fd, *mem, mem_sz)) < 0
			|| (uint64_t)read_ret != mem_sz) {
		if (*mem)
			free(*mem);
		if (fd >= 0)
			close(fd);
		return (-1);
	}
	return (0);
}

static rets_t		test_alg(alg_t alg, uint64_t max_sz) {
	const mem_test_t	mem_tests[] = {
		md5_mem, sha224_mem, sha256_mem,
		sha384_mem_test, sha512_mem_test,
	};
	const file_test_t	file_tests[] = {
		md5_file, sha224_file, sha256_file,
		sha384_file, sha512_file,
	};
	FILE		*file;
	uint64_t	sz;
	uint8_t		*mem = NULL;
	char		*expect;

	if (rand_mem(&mem, max_sz))
		return (test_ret(RT_RND_GEN));
	for (sz = 0; sz <= max_sz; ++sz) {
		expect = expect_hash(alg, mem, sz);
		if (!(file = fmemopen(mem, sz, "r"))) {
			free(mem);
			return (test_ret(RT_MEM_FILE));
		}
		if (strcmp(expect, mem_tests[alg](mem, sz))
				|| strcmp(expect, file_tests[alg](file))) {
			fclose(file);
			free(mem);
			return (test_ret(RT_KO, ALG_STR[alg], sz));
		}
		fclose(file);
	}
	free(mem);
	return (test_ret(RT_OK, ALG_STR[alg], max_sz));
}

int			main(void) {
	pid_t			pids[ALG_NB];
	uint64_t		fork_nb = ALG_NB;
	uint8_t			i;
	rets_t			rets = 0;
	int				status;

	for (i = 0; i < fork_nb; ++i) {
		if (!(pids[i] = fork()))
			return (test_alg(i, TEST_MAX_SZ));
		if (pids[i] < 0) {
			fork_nb = i;
			rets |= test_ret(RT_FORK, ALG_STR[i]);
			break;
		}
	}
	for (i = 0; i < fork_nb; ++i) {
		waitpid(pids[i], &status, WUNTRACED);
		rets |= (WIFEXITED(status))
			? WEXITSTATUS(status) : test_ret(RT_EXIT);
	}
	return (rets);
}
