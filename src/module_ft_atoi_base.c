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
		{ "12", "01234567889" },
		{ "1", "1" },
	};
	int	expected[] = {
		123, 15, 15, 255, 7, 128, 0, 0
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
