/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:03:06 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/14 19:40:35 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test_includes.h"

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

static char		*get_filename(char *path) {
	char	*name, *new_name;

	for (name = strtok(path, "/"); (new_name = strtok(NULL, "/")); name = new_name);
	return (name);
}

int			run_tests(int argc, char **argv, exp_test_t exp_test, mem_test_t mem_test, file_test_t file_test) {
	FILE		*file;
	uint64_t	mem_sz = MEM_SZ, sz;
	uint8_t		*mem = NULL;
	char		*expect;

	if (argc > 1) {
		mem_sz = (uint64_t)strtoll(argv[1], NULL, 10);
		if ((int64_t)mem_sz < 1) {
			fprintf(stderr, "Error: Invalid parameter\n");
			return (1);
		}
	}
	if (rand_mem(&mem, mem_sz)) {
		fprintf(stderr, "Error: Can't generate random data\n");
		return (2);
	}
	argv[0] = get_filename(argv[0]);
	for (sz = 0; sz <= mem_sz; ++sz) {
		expect = exp_test(mem, sz);
		if (!(file = fmemopen(mem, sz, "r"))) {
			fprintf(stderr, "Error: Can't create test file\n");
			free(mem);
			return (3);
		}
		if (strcmp(expect, mem_test(mem, sz))
				|| strcmp(expect, file_test(file))) {
			printf("%s with %lu byte(s): KO\n", argv[0], sz);
			fclose(file);
			free(mem);
			return (4);
		}
		fclose(file);
	}
	printf("%s with up to %lu byte(s): OK\n", argv[0], mem_sz);
	free(mem);
	return (0);
}
