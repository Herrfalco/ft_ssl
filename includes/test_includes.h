/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_includes.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:45:11 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/14 16:46:57 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_INCLUDES_H
#define TEST_INCLUDES_H

#include "includes.h"
#include <math.h>
#include <fcntl.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include <unistd.h>

#define MEM_SZ		(uint64_t)pow(2, 14)
#define RAND_NB		10

typedef char	*(*exp_test_t)(uint8_t *, uint64_t sz);
typedef char	*(*mem_test_t)(uint8_t *, uint64_t sz);
typedef char	*(*file_test_t)(FILE *file);

int				run_tests(int argc, char **argv, exp_test_t exp_test, mem_test_t mem_test, file_test_t file_test);
void			str_first_rep(char *str, char targ, char val);

#endif	// TEST_INCLUDES_H
