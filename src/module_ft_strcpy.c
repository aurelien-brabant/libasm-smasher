/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_ft_strcpy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:15:49 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 22:43:50 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "smasher.h"
#define MAX_STRCPY_BUF 10000

void	module_ft_strcpy(t_module *module)
{
	const char *srcs[] = { 
		"hello world",
		"copied text",
		"some text again",
		"",
		"x",
		"zz",
		"333",
		"2202",
		"he\0",
		"00e3\\t"
	};
	char	expected_dst[MAX_STRCPY_BUF];
	char	actual_dst[MAX_STRCPY_BUF];
	char	*actual_ret;

	for (size_t i = 0, length = sizeof (srcs) / sizeof (char *); i < length; ++i) {
		save_preserved_reg();
		strcpy(expected_dst, srcs[i]);
		actual_ret = ft_strcpy(actual_dst, srcs[i]);

		/* test return value */
		if (actual_ret != actual_dst)
			smash(module, "BAD RETURN VALUE!\nactual_dst = %p, return value = %p", actual_dst, actual_ret);
		/* test copy */
		if (strcmp(actual_dst, expected_dst) != 0)
			smash(module, "EXPECTED DEST STRING != ACTUAL DEST STRING!\nFor source string=\"%s\"\nAfter call to strcpy, dst=\"%s\"\nAfter call to YOUR ft_strcpy, dst=\"%s\"",
					srcs[i], expected_dst, actual_dst);
		/* ensure registers have been preserved by ft_strcpy */
		else if (smash_assert_reg(module) && actual_ret == actual_dst)
			module->passed++;
		module->tested++;
	}
	smash_end_module(module);
}
