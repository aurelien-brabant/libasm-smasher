/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_ft_strcmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 11:27:23 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 22:42:55 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "smasher.h"

void	module_ft_strcmp(t_module *module)
{
	const char	*strings[][2] = {
		{ "we are indentical", "we are identical" },
		{ "we are not indenticaL", "we are not identical" },
		{ "Hello world", "hello world" },
		{ "hello empty", "" },
		{ "", "hello empty" },
		{ "", "" },
		{ "WhErE iS bRiAn ?", "WhERE iS bRiAn"},
		{ "dans la KOUIZINE!", "dans la COUIZINE!"},
		{ "le desordre", "le desodrre" },
		{ "l'ordre", "l'ordre" },
		{ "long string long string long string long string long string long string long string long string long string",
			"long string long string long string long string long string long string long string long string long string"
		},
		{ "z", "z" },
		{ "e\0", "e" },
		{ "vvvvV", "vvVvv" },
	};
	/* Iterate over each test string, call the true function and the wrong one, and see if there's a difference */
	for (size_t i = 0, length = sizeof (strings) / sizeof (char *[2]); i < length; ++i) {
		save_preserved_reg();
		size_t	actual = ft_strcmp(strings[i][0], strings[i][1]);
		size_t	expected = strcmp(strings[i][0], strings[i][1]);

		/* if sign is not the same, smash! */
		if (!((actual > 0 && expected > 0) || (actual == 0 && expected == 0) || (actual < 0 && expected < 0)))
			smash(module, "strcmp(\"%s\", \"%s\")    => %ld\nft_strcmp(\"%s\", \"%s\") => %ld", 
					strings[i][0], strings[i][1], expected, strings[i][0], strings[i][1], actual);
		if (smash_assert_reg(module) && actual == expected)
			module->passed++;
		module->tested++;
	}
	smash_end_module(module);
}
