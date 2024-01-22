/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:53:44 by subpark           #+#    #+#             */
/*   Updated: 2024/01/21 20:41:54 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	red_error_handle(t_cmd *type)
{
	if (type->cmdstr[0][0] == '<' || type->cmdstr[0][0] =='>')
	{
		g_exit_status = 0;
		exit (g_exit_status);
	}
	else
		return ;
}

void	execute_simple_cmd(t_cmd *cmd, t_stdio **stdios, t_envp *env)
{
	static int		pipefd[2] = {-1, -1};
	static int		new_pipe[2];
	int				old_pipe[2];
	pid_t			pid;

	if (pipefd[0] != -1) //for excepting the case of first time
	{
		old_pipe[0] = dup(new_pipe[0]);
		close(new_pipe[0]);
	}
	if (pipe(new_pipe) == -1)
		return (perror("Pipe: "));//exit with signals
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	else if (pid == 0)
	{
		update_redirfd(pipefd, *stdios);
		update_pipefd(&pipefd, cmd->pipe_exist, old_pipe, new_pipe);
		if (check_builtin(cmd->left_child) == 0)
		{
			red_error_handle(cmd->left_child);
			int k = print_error_cmd(cmd->left_child, env);
	 		if (k == 0)
				exec(cmd->right_child->cmdstr, env);
		}
		exit(g_exit_status);
	}
	else
	{
		waitpid(0, &g_exit_status, 0);
		if (g_exit_status == 256)
			g_exit_status = 127;
		else if (g_exit_status == 512)
			g_exit_status = 1;
		if (check_builtin(cmd->left_child))
			builtin_action(cmd->right_child, cmd->right_child->cmdstr, env);
		write_pipefd(&pipefd, cmd->pipe_exist, old_pipe, new_pipe);
		free_stdios(*stdios);
		*stdios = NULL;
	}
}

void	execute_simple_redirect(t_cmd *node, t_stdio **stdios)
{
	t_stdio	*redirection;
	t_stdio *curr;

	redirection = (t_stdio *)malloc(sizeof(t_stdio));
	if (*stdios == NULL)
	{
		redirection->filename = node->right_child->cmdstr[0];
		redirection->re_type = redirect_type(node->left_child);
		redirection->next_stdio = NULL;
		*stdios = redirection;
	}
	else
	{
		redirection->filename = node->right_child->cmdstr[0];
		redirection->re_type = redirect_type(node->left_child);
		redirection->next_stdio = NULL;
		curr = *stdios;
		while (curr->next_stdio)
			curr = curr->next_stdio;
		curr->next_stdio = redirection;
	}
}

void	execute_tree(t_cmd *node, t_stdio **stdios, t_envp *envs)
{
	if (node->node_type == NODE_CMD || node->node_type == NODE_REDIRECTS)
		return ;
	else if (node->node_type == NODE_PIPE)
		;
	else if (node->node_type == NODE_SIMPLE_CMD)
		execute_simple_cmd(node, stdios, envs);
	else if (node->node_type == NODE_SIMPLE_REDIRECT)
		execute_simple_redirect(node, stdios);
}

void	search_tree(t_cmd *node, char **envp, t_envp *env)
{
	static t_stdio	*stdios;

	if (node == NULL)
		return ;
	execute_tree(node, &stdios, env);
	if (node->left_child && (node->left_child->node_type != NODE_RED_TYPE ||
		node->left_child->node_type != NODE_FILE_PATH))
		search_tree(node->left_child, envp, env);
	if (node->right_child && (node->right_child->node_type != NODE_FILE_NAME ||
		node->right_child->node_type != NODE_ARGV))
		search_tree(node->right_child, envp, env);
}