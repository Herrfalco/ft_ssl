/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:38:43 by fcadet            #+#    #+#             */
/*   Updated: 2022/10/27 17:17:46 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/types.h"
#include "../../hdrs/defines.h"

int		disp_help(void) {
	const char	*help = "ft_ssl ALG [OPTS] [FILES]\n" \
		"  ALG:\n" \
		"    md5\n" \
		"    sha224\n" \
		"    sha256\n" \
		"    sha384\n" \
		"    sha512\n" \
		"  OPTS:\n" \
		"    -p	Echo stdin\n" \
		"    -q	Quiet mode\n" \
		"    -r	Reverse format\n" \
		"    -s	Hash string\n";

	printf("%s", help);
	return (0);
}

err_t	error(err_t err, ...) {
	const char		*err_str[] = {
		"Unknown algorithm \"%s\"",
		"Duplicated option \"%s\"",
		"No string specified",
		"Can't hash stdin",
		"Can't hash memory",
		"Can't hash file \"%s\"",
	};
	char					buff[BUFF_SZ];
	va_list					datas;

	va_start(datas, err);
	vsnprintf(buff, BUFF_SZ, err_str[err - 1], datas);
	va_end(datas);
	fprintf(stderr, "Error: %s\n", buff);
	return (err);
}
