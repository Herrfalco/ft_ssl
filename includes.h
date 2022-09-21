/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herrfalco <fcadet@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 06:36:40 by herrfalco         #+#    #+#             */
/*   Updated: 2022/09/21 07:06:53 by herrfalco        ###   ########.fr       */
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

char		*md5_result(md5_t *md5);
md5_t		*md5_new(void);
void		md5_mem(md5_t *md5, uint8_t *mem, uint64_t size);

#endif // INCLUDES_H
