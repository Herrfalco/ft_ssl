/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unifiers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:06:57 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/25 11:57:54 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_includes.h"

char		*sha384_mem_test(uint8_t *str, uint64_t sz) {
	return (sha384_mem(str, sz));
}

char		*sha512_mem_test(uint8_t *str, uint64_t sz) {
	return (sha512_mem(str, sz));
}
