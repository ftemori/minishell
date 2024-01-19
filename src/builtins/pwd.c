/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:13:40 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/15 12:13:42 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	our_pwd(char **av)
{
	char	path[1024];
	int		i;

	i = 0;
	while (av[i])
		i++;
	if (i > 1)
	{
		printf("Look up how to use 'pwd' please!!\n");
		return ;
	}
	if (getcwd(path, sizeof(path)) == NULL)
	{
		g_exit_status = 127;
		return ;
	}
	write(1, path, f_strlen(path));
	write(1, "\n", 1);
	g_exit_status = 0;
	return ;
}
