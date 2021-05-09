#include <limits.h>
#include "smasher.h"

void	module_ft_atoi_base(t_module *module)
{
	const char	*args[][2] = {
		{"123", "0123456789"},
		{ "1111", "01" },
		{ "F", "0123456789ABCDEF"},
		{ "ff", "0123456789abcdef"},
		{ "         \t\v\r  7    ", "012345678" },
		{ "\v\v\v\v\t\t\t\r\r\r\r\r   \r\v\r10000000", "01" },
		{ "+--12", "01234567889" },
		{ "1", "1" },
		// INT_MAX in octal
		{ "17777777777", "01234567" },
		// INT_MIN in binary
		{ "\v\r   \t\v-+-+-++++++++10000000000000000000000000000000", "01" },
		{ "0", "01" },
		{ "p", "poneyvif" },
		{ "o", "poneyvif" },
		/* INCORRECT BASES */
		{ "123", "01234567889" }, /* duplicated */
		{ "12", "0123456 789" }, /* base with space */
		{ "12", "0123456\v789" }, /* base with space */
		{ "12", "0123456\f789" }, /* base with space */
		{ "12", "0123456\t789" }, /* base with space */
		{ "12", "0123456\r789" }, /* base with space */
		{ "12", "0123456+789" }, /* base with space */
		{ "12", "0123456-789" }, /* base with sign */
		/* Stop at first non-base char */
		{ "-12a3", "0123456789" },
		{ "\v\t\t\t\t\t\r \v\v\v \t\t\t\t   a1234", "0123456789" }, 
	};

	int	expected[] = {
		123, 15, 15, 255, 7, 128, 0, 0, INT_MAX, INT_MIN, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, -12, 0
	};
	size_t	size = sizeof (args) / (sizeof (char *) * 2);

	for (size_t i = 0; i < size; ++i) {
		int actual = ft_atoi_base(args[i][0], args[i][1]);
		if (actual == expected[i]) {
			if (smash_assert_reg(module)) {
				module->passed++;
			}
		}
		else
			smash(module, "ft_atoi_base(\"%s\", \"%s\")\nexpected: %d\nactual:%d"
					, args[i][0], args[i][1], expected[i], actual);
		module->tested++;
	}
	smash_end_module(module);
}
