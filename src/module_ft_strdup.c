/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_ft_strdup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:27:23 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 22:03:15 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "smasher.h"

void	module_ft_strdup(t_module *module)
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
		char	*dup = ft_strdup(strings[i]);

		/* ensure string is writable */
		dup[0] = strings[i][0];
		if (strcmp(dup, strings[i]) != 0)
			smash(module, "DUPED STRING IS NOT IDENTICAL TO THE SOURCE\nFor source string=\"%s\"\nCreated duplicate dup=\"%s\"\n", strings[i], dup);
		else if (smash_assert_reg(module))
			module->passed++;
		module->tested++;
		free(dup);
	}
	smash_end_module(module);
}
