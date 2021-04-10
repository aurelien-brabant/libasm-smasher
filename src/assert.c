/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 10:30:25 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 22:27:54 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include "smasher.h"

bool	smash(t_module *module, const char *err, ...)
{
	va_list	ap;

	va_start(ap, err);
	fprintf(stderr, "\n>>>>>    \033[1;31mERROR\033[0m     <<<<<\n");
	vfprintf(stderr, err, ap);
	fprintf(stderr, "\n\nFrom MODULE %s, TEST %ld\n", module->name, module->tested);
	fprintf(stderr, ">>>>> \033[1;39mEND OF ERROR \033[0m<<<<< \n\n");
	module->errors++;
	return (false);
}

/*
 * Check if registers rbx, rbp, r12, r13, r14 and r15 registers have been
 * preserved since the last call to save_preserved_reg.
*/

bool	smash_assert_reg(t_module *module)
{
	t_unpreserved_reg	ureg;

	(void)module;
	check_preserved_reg(&ureg);
	if (ureg.reg != NULL)
		return (smash(module, "%s register hasn't been preserved by your ASM routine! Saved value was %llx, got %llx.", ureg.reg, ureg.expected, ureg.actual));
	return (true);
}

void	smash_end_module(t_module *module)
{
	printf("\n***** \033[1;34m   MODULE SUMMARY    \033[0m*****\n");
	printf("MODULE: \033[0;35m%s\033[0m\n", module->name);
	printf("TOTAL : %ld/%ld passed.\n", module->passed, module->tested);
	printf("ERRORS: %s%ld\033[0m\n", module->errors == 0 ? "\033[1;32m" : "\033[1;31m", module->errors);
	printf("***** \033[1;39mEND OF MODULE SUMMARY \033[0m*****\n");
}
