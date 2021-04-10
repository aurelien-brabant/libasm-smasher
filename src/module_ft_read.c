/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   module_ft_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:09:48 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/10 18:12:10 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
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
#define READ_SIZE 100
#define READ_BUFFER_SIZE 100000

void	module_ft_read(t_module *module)
{
	const char	*filepaths[] = {
		"asset/loremipsum1"
	};
	char		expected[READ_BUFFER_SIZE] = { 0 };
	char		actual[READ_BUFFER_SIZE] = { 0 };
	int			actual_ret = -1;
	int			expected_ret = -1;
	int			ref_errno, actual_errno;

	for (size_t i = 0, length = sizeof (filepaths) / sizeof (char *); i < length; ++i) {
		char	*filename = NULL;
		char	*filename_ptr = NULL;

		if ((filename = strdup(filepaths[i])) != NULL) {
			filename_ptr = filename;
			filename = basename(filename);
		}

		/* no open check is performed, if it fails it will make read fail too, which is to be expected for some tests */
		int fd = open(filepaths[i], O_RDONLY);
		errno = 0;
		
		/* litteraly put the file's content in the expected buffer */
		while ((expected_ret = read(fd, expected, READ_SIZE)) > 0)
			;
		ref_errno = errno;
		lseek(fd, SEEK_SET, 0);
		/* put the file's content in actual buffer */ 
		while ((actual_ret = read(fd, actual, READ_SIZE)) > 0)
			;
		actual_errno = errno;

		/* ensure errno is set correctly. If no error occured, errno will be
		   assumed to be zero. It is automatically set to zero at each test,
		   but normally errno is not modified by successfull calls. */
		if (ref_errno != actual_errno)
			smash(module, "ERRNO HAS NOT BEEN SET CORRECTLY!\n reference errno after call to read: %d\nactual errno"
					"after call to ft_read: %d\n", ref_errno, actual_errno);

		/* check if read buffers are lexicographically the same */
		if (strcmp(expected, actual) != 0)
		{
			/* buffers differ, so let's write both of them into files
			and execute a diff -u on them */

			char logfile[FILENAME_MAX + 1];
			char syscmd[26 + FILENAME_MAX + 1] = { 0 };

			snprintf(logfile, FILENAME_MAX + 1, "%s.read.diff", filename);
			snprintf(syscmd, 26 + FILENAME_MAX + 1, "diff -u .tmp1 .tmp2 > log/%s", logfile);

			int actual_fd = open(".tmp1", O_RDWR | O_CREAT, S_IREAD);
			int expected_fd = open(".tmp2", O_RDWR | O_CREAT, S_IREAD);

			write(actual_fd, actual, strlen(actual));
			write(expected_fd, expected, strlen(expected));
			system(syscmd);

			/* cleanup */
			remove(".tmp1"); remove(".tmp2");
			close(actual_fd); close(expected_fd);

			smash(module, "READ BUFFERS DIFFER!\nDifference has been outputed in log/%s", logfile);
		}
		else if (smash_assert_reg(module) && ref_errno == actual_errno)
			module->passed++;
		module->tested++;
		free(filename_ptr);
		close(fd);
	}
	smash_end_module(module);
}
