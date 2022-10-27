/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:36:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/22 09:39:45 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes.h"

void		sha512_proc_block(sha512_t *sha512, uint64_t *block);
void		sha512_proc_last_block(sha512_t *sha512, uint8_t *block_buff, uint128_t sav_sz, uint128_t rem_sz);

static char		*sha384_result(sha384_t *sha384) {
	static char		buff[BUFF_SZ];

	sprintf(buff, "%016lx%016lx%016lx%016lx%016lx%016lx",
			sha384->a, sha384->b, sha384->c, sha384->d,
			sha384->e, sha384->f);
	return (buff);
}

static sha384_t	*sha384_new(void) {
	static sha384_t		new;

	new.a = 0xcbbb9d5dc1059ed8;
	new.b = 0x629a292a367cd507;
	new.c = 0x9159015a3070dd17;
	new.d = 0x152fecd8f70e5939;
	new.e = 0x67332667ffc00b31;
	new.f = 0x8eb44a8768581511;
	new.g = 0xdb0c2e0d64f98fa7;
	new.h = 0x47b5481dbefa4fa4;
	return (&new);
}

char		*sha384_mem(uint8_t *mem, uint128_t sz) {
	sha384_t	*sha384 = sha384_new();

	return (hash_mem_64(sha384, mem, sz, sha512_proc_block, sha512_proc_last_block) ? NULL : sha384_result(sha384));
}
char		*sha384_file(FILE *file) {
	sha384_t	*sha384 = sha384_new();

	return (hash_file_64(sha384, file, sha512_proc_block, sha512_proc_last_block) ? NULL : sha384_result(sha384));
}
