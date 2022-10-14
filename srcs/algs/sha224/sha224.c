/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:32:13 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/14 19:38:17 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/includes.h"

void		sha256_proc_block(sha256_t *sha256, uint32_t *block);
void		sha256_proc_last_block(sha256_t *sha256, uint8_t *block_buff, uint64_t sav_sz, uint64_t rem_sz);

static char		*sha224_result(sha224_t *sha224) {
	static char		buff[BUFF_SZ];

	sprintf(buff, "%08x%08x%08x%08x%08x%08x%08x",
			sha224->a, sha224->b, sha224->c, sha224->d,
			sha224->e, sha224->f, sha224->g);
	return (buff);
}

static sha224_t	*sha224_new(void) {
	static sha224_t		new;


	new.a = 0xc1059ed8;
	new.b = 0x367cd507;
	new.c = 0x3070dd17;
	new.d = 0xf70e5939;
	new.e = 0xffc00b31;
	new.f = 0x68581511;
	new.g = 0x64f98fa7;
	new.h = 0xbefa4fa4;
	return (&new);
}

char		*sha224_mem(uint8_t *mem, uint64_t sz) {
	sha224_t	*sha224 = sha224_new();

	return (hash_mem_32(sha224, mem, sz, sha256_proc_block, sha256_proc_last_block) ? NULL : sha224_result(sha224));
}

char		*sha224_file(FILE *file) {
	sha224_t	*sha224 = sha224_new();

	return (hash_file_32(sha224, file, sha256_proc_block, sha256_proc_last_block) ? NULL : sha224_result(sha224));
}
