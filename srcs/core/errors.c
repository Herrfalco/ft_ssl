/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcadet <fcadet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:38:43 by fcadet            #+#    #+#             */
/*   Updated: 2022/11/09 18:11:39 by fcadet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/utils.h"

int		disp_help(void) {
	int i;

	printf("\n%-15s\t\tft_ssl DIG [OPTS] [...files...]\n\n" \
			"\tDIG:\n", "Message Digest:");
	for (i = 0; i < DIG_NB; ++i)
		printf("\t\t%s\n", ALG_STR[i]);
	printf("\tOPTS:\n");
	for (i = 0; i < DIG_O_NB; ++i)
		printf("\t\t%s\t%s\n", OPT_STR[i], OPT_INFO[i]);
	printf("\n%-15s\t\tft_ssl CIP [OPTS]\n\n\tCIP:\n",
			"Cypher:");
	for (i = DIG_NB; i < ALG_NB; ++i)
		printf("\t\t%s\n", ALG_STR[i]);
	printf("\tOPTS:\n");
	for (i = DIG_O_NB; i < OPT_NB; ++i)
		printf("\t\t%s\t%s\n", OPT_STR[i], OPT_INFO[i]);
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
		"Input/Output error",
		"Can't use \"%s\" with \"%s\"",
	};
	char					buff[BUFF_SZ];
	va_list					datas;

	va_start(datas, err);
	vsnprintf(buff, BUFF_SZ, err_str[err - 1], datas);
	va_end(datas);
	fprintf(stderr, "Error: %s\n", buff);
	return (err);
}
