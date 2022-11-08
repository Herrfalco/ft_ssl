/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:06:27 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/08 08:12:14 by herrfalco        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
#define DEFINES_H

#define PAGE_SZ			4096
#define BUFF_SZ			256
#define BLOCK_SZ		64
#define BIG_BLOCK_SZ	128
#define BIG_RND_NB		80
#define	OPT_NB			4
#define ALG_NB			5

#ifdef __APPLE__
	#define RES_384			"%016llx%016llx%016llx%016llx%016llx%016llx"
	#define RES_512			"%016llx%016llx%016llx%016llx%016llx%016llx%016llx%016llx"
#else
	#define RES_384			"%016lx%016lx%016lx%016lx%016lx%016lx"
	#define RES_512			"%016lx%016lx%016lx%016lx%016lx%016lx%016lx%016lx"
#endif // __APPLE__

#endif // DEFINES_H
