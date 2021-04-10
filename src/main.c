/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 12:16:04 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 12:31:21 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "smasher.h"

int	main(void)
{
	t_module	module[MODULE_MAX + 1] = {
		{
			"ft_strlen",
			module_ft_strlen,
			0, 0, 0
		},
		{
			"ft_strlen",
			module_ft_strlen,
			0, 0, 0
		}
	};
	size_t		i = 0;
	size_t		modules_passed = 0;

	save_preserved_reg();

	/* Run test modules */
	while (module[i].module_handler != NULL)
	{
		module[i].module_handler(&module[i]);	
		if (module[i].errors == 0)
			++modules_passed;
		++i;
	}
	puts("\n############### \033[1;33mSMASHER SUMMARY \033[0m###############");
	printf("MODULES: %ld/%ld passed.\n", modules_passed, i);
	if (modules_passed == i)
		puts("\033[0;32mYour libasm passed all the modules, congrats :D !\n");
	else
		puts("\033[0;31mIt seems that your libasm will need a little bit of additional work! Keep it up!\n");
}
