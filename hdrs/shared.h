/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:45:55 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:04:30 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHARED_H
#define SHARED_H

#include "types.h"

void		sha256_proc_block(sha256_t *sha256, uint32_t *block);
void		sha256_proc_last_block(sha256_t *sha256, uint8_t *block_buff, uint64_t sav_sz, uint64_t rem_sz);
void		sha512_proc_block(sha512_t *sha512, uint64_t *block);
void		sha512_proc_last_block(sha512_t *sha512, uint8_t *block_buff, uint128_t sav_sz, uint128_t rem_sz);

#endif // SHARED_H
