/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:11:50 by subpark           #+#    #+#             */
/*   Updated: 2024/01/21 13:30:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error_cmd(t_cmd *file_path, t_envp *env)
{
	char	*path_buf;

	path_buf = path_pointer(file_path->cmdstr, env);
	if (!path_buf)
	{
		printf("%s: ", file_path->cmdstr[0]);
		if (errno != 2)
			perror("");
		else
		{
			g_exit_status = 1;
			printf("command not found\n");
			return (-1);
		}
	}
	free(path_buf);
	return (0);
}

int	check_builtin(t_cmd *file_path)
{
	if (!ft_strcmp(file_path->cmdstr[0], "echo") || !ft_strcmp(file_path->cmdstr[0], "cd")
		|| !ft_strcmp(file_path->cmdstr[0], "pwd") || !ft_strcmp(file_path->cmdstr[0], "export")
		|| !ft_strcmp(file_path->cmdstr[0], "unset") || !ft_strcmp(file_path->cmdstr[0], "env")
		|| !ft_strcmp(file_path->cmdstr[0], "exit"))
		return (1);
	else
		return (0);
}

void	builtin_action(t_cmd *builtin, char **cmdline, t_envp *env)
{
	if (!ft_strcmp(builtin->cmdstr[0], "echo"))
		our_echo(cmdline);
	else if (!ft_strcmp(builtin->cmdstr[0], "pwd"))
		our_pwd(builtin->cmdstr, 1);
	else if (!ft_strcmp(builtin->cmdstr[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(builtin->cmdstr[0], "exit"))
		exit_command(builtin->cmdstr);
	else if (!ft_strcmp(builtin->cmdstr[0], "unset"))
		ft_unset(builtin->cmdstr[1], env);
	else if (!ft_strcmp(builtin->cmdstr[0], "export"))
		export(builtin->cmdstr + 1, env);
	else if (!ft_strcmp(builtin->cmdstr[0], "cd"))
		change_directory(builtin->cmdstr, env);
}