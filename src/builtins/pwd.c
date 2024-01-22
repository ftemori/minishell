/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:13:40 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/20 23:55:20 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*our_pwd(char **av, int pflag)
{
	char	*path;
	char	path1[1024];
	int		i;

	i = 0;
	path = malloc(1024 * sizeof(char));
	while (av[i] != NULL && av)
		i++;
	if (i > 1)
	{
		printf("Look up how to use 'pwd' please!!\n");
		return (NULL);
	}
	if (getcwd(path1, sizeof(path1)) == NULL)
	{
		g_exit_status = 127;
		return (NULL);
	}
	ft_strlcpy(path, path1, f_strlen(path1) + 1);
	if (pflag == 1)
	{
		write(1, path, f_strlen(path));
		write(1, "\n", 1);
		free(path);
		g_exit_status = 0;
	}
	else
		return (path);
	return (NULL);
}
