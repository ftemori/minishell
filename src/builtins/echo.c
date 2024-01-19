/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:08:59 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/15 12:09:01 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
}

int	f_putstr(char *s)
{
	write(1, s, ft_strlen(s));
	return (0);
}

int	f_strchr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

void	our_echo(char **av)
{
	int		i;
	char	c;

	c = 'y';
	i = 1;
	if (f_strcmp("-n", av[1]) == 0)
	{
		i = 2;
		c = 'n';
	}
	while (av[i] != NULL)
	{
		f_putstr(av[i]);
		if (av[i + 1] != NULL)
			write(1, " ", 1);
		if (av[i + 1] == NULL && c == 'y')
			write(1, "\n", 1);
		i++;
	}
	return ;
}
