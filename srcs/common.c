/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:54:13 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:21:51 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/types.h"
#include "../hdrs/defines.h"

int			hash_mem_32(vals_32_t *vals, uint8_t *mem, uint64_t sz,
		proc_block_32_t proc_block, proc_last_block_32_t proc_last_block) {
	uint8_t			block_buff[BLOCK_SZ] = { 0 };
	uint64_t		sav_sz = sz * 8, max_sz = 0;

	if (sz > --max_sz / 8)
		return (-1);
	for (; sz >= BLOCK_SZ;
			mem += BLOCK_SZ, sz -= BLOCK_SZ)
		proc_block(vals, (uint32_t *)mem);
	memcpy(block_buff, mem, sz);
	proc_last_block(vals, block_buff, sav_sz, sz);
	return (0);
}

int			hash_file_32(vals_32_t *vals, FILE *file, proc_block_32_t proc_block, proc_last_block_32_t proc_last_block) {
	uint8_t			block_buff[BLOCK_SZ] = { 0 };
	uint64_t		sz = 0, max_sz = 0;
	ssize_t			read_ret;

	while ((read_ret = fread(block_buff, 1, BLOCK_SZ, file)) > 0) {
		if (sz + read_ret > (max_sz - 1) / 8 || ferror(file))
			return (-1);
		sz += read_ret;
		if (read_ret != BLOCK_SZ)
			break;
		proc_block(vals, (uint32_t *)block_buff);
	}
	bzero(block_buff + read_ret, BLOCK_SZ - read_ret);
	proc_last_block(vals, block_buff, sz * 8, read_ret);
	return (0);
}

int			hash_mem_64(vals_64_t *vals, uint8_t *mem, uint128_t sz,
		proc_block_64_t proc_block, proc_last_block_64_t proc_last_block) {
	uint8_t			block_buff[BIG_BLOCK_SZ] = { 0 };
	uint128_t		sav_sz = sz * 8, max_sz = 0;

	if (sz > --max_sz / 8)
		return (-1);
	for (; sz >= BIG_BLOCK_SZ;
			mem += BIG_BLOCK_SZ, sz -= BIG_BLOCK_SZ)
		proc_block(vals, (uint64_t *)mem);
	memcpy(block_buff, mem, sz);
	proc_last_block(vals, block_buff, sav_sz, sz);
	return (0);
}

int			hash_file_64(vals_64_t *vals, FILE *file, proc_block_64_t proc_block, proc_last_block_64_t proc_last_block) {
	uint8_t			block_buff[BIG_BLOCK_SZ] = { 0 };
	uint128_t		sz = 0, max_sz = 0;
	ssize_t			read_ret;

	while ((read_ret = fread(block_buff, 1, BIG_BLOCK_SZ, file)) > 0) {
		if (sz + read_ret > (max_sz - 1) / 8 || ferror(file))
			return (-1);
		sz += read_ret;
		if (read_ret != BIG_BLOCK_SZ)
			break;
		proc_block(vals, (uint64_t *)block_buff);
	}
	bzero(block_buff + read_ret, BIG_BLOCK_SZ - read_ret);
	proc_last_block(vals, block_buff, sz * 8, read_ret);
	return (0);
}
