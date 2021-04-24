/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smasher.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrabant <abrabant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 09:06:20 by abrabant          #+#    #+#             */
/*   Updated: 2021/04/24 17:28:00 by abrabant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SMASHER_H
# define SMASHER_H
# include <stdint.h>
# include <stddef.h>
# include <stdbool.h>
# define MODULE_MAX 30

typedef struct s_module
{
	const char	*name;
	void		(*module_handler)(struct s_module *module);
	size_t		errors;
	size_t		passed;
	size_t		tested;
}	t_module;

extern const char	*current_module;

/* size in memory: 8 * 3 = 24 (no alignment required). */

typedef struct s_unpreserved_reg
{
	uint64_t	expected;
	uint64_t	actual;
	char		*reg;
}	t_unpreserved_reg;

void	save_preserved_reg(void);
void	check_preserved_reg(t_unpreserved_reg *ureg);

bool	smash(t_module *module, const char *err, ...);
bool	smash_assert_reg(t_module *module);
void	smash_end_module(t_module *module);

void	module_ft_strlen(t_module *module);
void	module_ft_strcmp(t_module *module);
void	module_ft_strcpy(t_module *module);
void	module_ft_strdup(t_module *module);
void	module_ft_read(t_module *module);
void	module_ft_write(t_module *module);

void	module_ft_atoi_base(t_module *module);

/* libasm prototypes */
int		ft_write(int fd, const void *buf, size_t n);
int		ft_read(int fd, void *buf, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
int		ft_atoi_base(const char *s, const char *base);

# endif
