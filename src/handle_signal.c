/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:23:06 by irivero-          #+#    #+#             */
/*   Updated: 2024/01/20 22:24:50 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.*/
void    handle_signal(int sign)
{
	pid_t	pid;
	int	status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sign == SIGINT)
	{
		if (pid == -1)
        	{
			ft_putstr_fd("\n", 1);
			generate_prompt();
			g_exit_status = 1;
    		}
		else
			ft_putstr_fd("\n", 1);
	}
	else if (sign == SIGQUIT)
	{
		if (pid == -1)
			ft_putstr_fd("\b\b	\b\b", 1);
		else
			ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}