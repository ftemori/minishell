/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 02:17:56 by ubuntu            #+#    #+#             */
/*   Updated: 2024/02/12 16:26:04 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	if_pflag_is_one(char *path)
{
	write(1, path, f_strlen(path));
	write(1, "\n", 1);
	free(path);
	g_exit_status = 0;
	return ;
}

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
		return (NULL);
	if (getcwd(path1, sizeof(path1)) == NULL)
	{
		g_exit_status = 127;
		return (NULL);
	}
	g_exit_status = 0;
	ft_strlcpy(path, path1, f_strlen(path1) + 1);
	if (pflag == 1)
		if_pflag_is_one(path);
	else
		return (path);
	g_exit_status = 0;
	exit(g_exit_status);
	return (NULL);
}
