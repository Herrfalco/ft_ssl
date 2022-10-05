/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 12:36:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/05 18:06:14 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

char		*sha384_result(sha384_t *sha384) {
	static char		buff[BUFF_SZ];

	sprintf(buff, "%016lx%016lx%016lx%016lx%016lx%016lx",
			sha384->a, sha384->b, sha384->c, sha384->d,
			sha384->e, sha384->f);
	return (buff);
}

sha384_t	*sha384_new(void) {
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

void		sha384_mem(sha384_t *sha384, uint8_t *mem, uint64_t size) {
	sha512_mem(sha384, mem, size);
}
