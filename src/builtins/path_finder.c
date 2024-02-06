/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:31:45 by ftemori           #+#    #+#             */
/*   Updated: 2024/02/06 18:31:48 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     var_finder(char **env, char *s)
{
        int     i;
        i = 0;
        while (env[i] != NULL)
        {
                if (f_strcmp(env[i], s) != -1)
                        return (i);
                i++;
        }
        return (-1);
}