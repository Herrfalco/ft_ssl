/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:32:13 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/03 18:45:11 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

char		*sha224_result(sha224_t *sha224) {
	static char		buff[BUFF_SZ];

	sprintf(buff, "%08x%08x%08x%08x%08x%08x%08x",
			sha224->a, sha224->b, sha224->c, sha224->d,
			sha224->e, sha224->f, sha224->g);
	return (buff);
}

sha224_t	*sha224_new(void) {
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

void		sha224_mem(sha224_t *sha224, uint8_t *mem, uint64_t size) {
	sha256_mem(sha224, mem, size);
}
