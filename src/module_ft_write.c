/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_ft_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:09:48 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 22:43:32 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <linux/limits.h>
#include <stdio.h>
#include <limits.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <libgen.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>

#include "smasher.h"
#define WRONG_FD -42

void	module_ft_write(t_module *module)
{
	const char	*strings[] = {
		"Hello world this is a string",
		"Another string to write !",
		"I love strings",
		"",
		"this is a long string this is a long string this is a long string this is a long string this is a long string this is a long string this is a long string",
		"e",
		"zzz",
		"c",
		"invalid_fd",
	};

	int	expected_fd = open(".tmp", O_RDWR | O_CREAT, S_IRWXU);
	int	actual_fd = open(".tmp2", O_RDWR | O_CREAT, S_IRWXU);
	int actual_errno, expected_errno;
	char syscmd[50] = { 0 };

	for (size_t i = 0, length = sizeof (strings) / sizeof (char *); i < length; ++i) {
		save_preserved_reg();
		errno = 0;
		if (strcmp(strings[i], "invalid_fd") == 0)
			write(WRONG_FD, strings[i], strlen(strings[i]));
		else
			write(expected_fd, strings[i], strlen(strings[i]));
		expected_errno = errno;

		errno = 0;
		/* test ft_write */
		if (strcmp(strings[i], "invalid_fd") == 0)
			ft_write(WRONG_FD, strings[i], strlen(strings[i]));
		else
			ft_write(actual_fd, strings[i], strlen(strings[i]));
		actual_errno = errno;

		if (actual_errno != expected_errno)
			smash(module, "ERRNO HAS NOT BEEN SET CORRECTLY!\n expected errno after call to read: %d\nactual errno"
					"after call to ft_read: %d\n", expected_errno, actual_errno);

		/* perform a diff to check if files are identical */
		snprintf(syscmd, 50, "diff -u .tmp .tmp2 > log/%ld.write.diff", i);
		if (system(syscmd) != 0)
			smash(module, "DIFF RETURNED NON-ZERO, WRITE DIFFERS:\n .diff file has been outputed to log/%ld.write.diff", i);
		/* dirty trick to remove the diff file easily if there's no error */
		else
		{
			snprintf(syscmd, 50, "log/%ld.write.diff", i);
			remove(syscmd);
			if (actual_errno == expected_errno)
				module->passed++;
		}
		module->tested++;
	}
	close(actual_fd);
	close(expected_fd);
	remove(".tmp"); remove(".tmp2");

	smash_end_module(module);
}
