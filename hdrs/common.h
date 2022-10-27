/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:02:06 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:05:40 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
#define COMMON_H

#include "types.h"

int		hash_mem_32(vals_32_t *vals, uint8_t *mem, uint64_t sz, proc_block_32_t proc_block, proc_last_block_32_t proc_last_block);
int		hash_file_32(vals_32_t *vals, FILE *file, proc_block_32_t proc_block, proc_last_block_32_t proc_last_block);
int		hash_mem_64(vals_64_t *vals, uint8_t *mem, uint128_t sz, proc_block_64_t proc_block, proc_last_block_64_t proc_last_block);
int		hash_file_64(vals_64_t *vals, FILE *file, proc_block_64_t proc_block, proc_last_block_64_t proc_last_block);

#endif // COMMON_H
