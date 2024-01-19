/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:10:16 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/15 12:10:18 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	f_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr(char *s)
{
	write(1, s, f_strlen(s));
	write(1, "\n", 1);
	return (0);
}

void	ft_env(t_envp *env)
{
	int	i;

	i = 0;
	while (env->envp[i] != NULL)
	{
		if (ft_putstr(env->envp[i]) == -1)
			return ;
		i++;
	}
	return ;
}
