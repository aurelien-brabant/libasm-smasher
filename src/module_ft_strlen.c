/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_ft_strlen.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:27:23 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 12:14:17 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "smasher.h"

void	module_ft_strlen(t_module *module)
{
	const char	*strings[] = {
		"",
		"Hello world",
		"Hey",
		"heyo",
		"h\0ello",
		"This is a very long string this is a very long string this is a very long string this is a very long string this is a very long string this is a very long string",
		"Somestringwithoutanyspace",
		"e",
		"z",
		"x",
		"\0",
		"sm",
		"smmm"
	};
	/* Iterate over each test string, call the true function and the wrong one, and see if there's a difference */
	for (size_t i = 0, length = sizeof (strings) / sizeof (char *); i < length; ++i) {
		size_t	actual = strlen(strings[i]);
		size_t	expected = strlen(strings[i]);

		if (actual != expected)
			smash(module, "strlen(\"%s\")    => %ld\nft_strlen(\"%s\") => %ld", strings[i], expected, strings[i], actual);
		if (smash_assert_reg(module) && actual == expected)
			module->passed++;
		module->tested++;
	}
	smash_end_module(module);
}
