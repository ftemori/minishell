/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chopper2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:53:26 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/21 03:11:35 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ifhelper(t_data *data, char *tmp, int i, int k)
{
	int	m;

	m = i;
	while (tmp[i] != '\'' && tmp[i] != '\0')
		i++;
	f_strcpy(data, tmp + m - 1, i + 1, k);
	i++;
	tmp = tmp + i;
	return (tmp);
}

char	*elsehelper(t_data *data, char *tmp, int i, int k)
{
	int	m;

	m = i;
	while (tmp[i] != '\"' && tmp[i] != '\0')
		i++;
	f_strcpy(data, tmp + m, i - 1, k);
	i++;
	tmp = tmp + i;
	return (tmp);
}

char	*if_cases(char *tmp, int *i, t_data *data, int k)
{
	int	l;

	l = 0;
	if (tmp[0] == '\0')
		return (NULL);
	while (tmp[l] == ' ')
		l++;
	tmp = tmp + l;
	if (tmp[0] == '\0')
	{
		data->array[k] = NULL;
		return (NULL);
	}
	while (tmp[*i] != '\0' && tmp[*i] != ' ' && \
	tmp[*i] != '=' && tmp[*i] != '\"' && tmp[*i] != '\'' && \
	tmp[*i] != '<' && tmp[*i] != '>' && tmp[*i] != '|' && tmp[*i] != ';')
		(*i)++;
	return (tmp);
}

int	ft_chopper(t_data *data, char *tmp, int k)
{
	int	i;

	i = 0;
	tmp = if_cases(tmp, &i, data, k);
	if (tmp == NULL)
		return (-1);
	if (tmp[0] == '\'')
		tmp = ifhelper(data, tmp, i + 1, k);
	else if (tmp[0] == '\"')
		tmp = elsehelper(data, tmp, i + 1, k);
	else if (tmp[0] != '=' && tmp[0] != '\0' && tmp[0] != '<' && \
	tmp[0] != '>' && tmp[0] != '|' && tmp[0] != ';')
		f_strcpy(data, tmp, i, k);
	else if ((tmp[0] == '>' && tmp[1] == '>') || \
	(tmp[0] == '<' && tmp[1] == '<'))
		i = f_strcpy(data, tmp, 2, k);
	else if (tmp[0] == '=' || tmp[0] == '<' || tmp[0] == '>' || tmp[0] == '|' || tmp[0] == ';')
		i = f_strcpy(data, tmp, 1, k);
	if (ft_chopper(data, tmp + i, ++k) == -1 || tmp[i] == '\0')
		data->array[k] = NULL;
	return (0);
}

int is_special_char(char *c)
{
	return (c[0] == '=' || c[0] == '<' || c[0] == '>' || c[0] == '|' || c[0] == ';' || \
	((c[0] == '<' && c[1] == '<') || (c[0] == '>' && c[1] == '>')));
}