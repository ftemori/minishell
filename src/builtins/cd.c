/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:06:39 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/15 12:06:43 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_directory(char **paths)
{
	char	*path;

	path = paths[1];
	if (!path)
		path = getenv("HOME");
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s", path);
		return ;
	}
}
