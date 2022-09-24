/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:36:40 by herrfalco         #+#    #+#             */
/*   Updated: 2022/09/24 09:38:49 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define BUFF_SZ		128
#define BLOCK_SZ	64

typedef struct		md5_s {
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
}					md5_t;

typedef struct		sha256_s {
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}					sha256_t;

typedef enum		rot_e {
	LEFT,
	RIGHT,
}					rot_t;

uint32_t		swap_end_32(uint32_t val);
uint64_t		swap_end_64(uint64_t val);
uint32_t		rot_32(uint32_t val, uint8_t n, rot_t typ);

char		*md5_result(md5_t *md5);
md5_t		*md5_new(void);
void		md5_mem(md5_t *md5, uint8_t *mem, uint64_t size);

#endif // INCLUDES_H
