/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chopper1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:50:57 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/16 10:50:59 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quo_num(char *tmp, t_data *data)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			s++;
		if (tmp[i] == '\"')
			d++;
		i++;
	}
	if ((s % 2 == 0 || s == 0) && (d % 2 == 0 || d == 0))
	{
		data->sqn = s;
		data->dqn = d;
		return (s);
	}
	return (-1);
}

char	*whileloop(char *sstr, char *str)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
		{
			sstr[k] = str[i];
			k++;
			i++;
		}
		else if (str[i] == '\"' && str[i + 1] != '\"')
		{
			sstr[k] = str[i];
			i++;
			k++;
		}
		else
			i += 2;
	}
	sstr[k] = '\0';
	return (sstr);
}

int	quo_arrangement(char *str)
{
	char	*sstr;

	sstr = malloc(strlen(str) * sizeof(char));
	whileloop(sstr, str);
	if (strlen(sstr) > 3 && sstr[0] == sstr[2] && sstr[0] != '\0')
	{
		free(sstr);
		return (-1);
	}
	if (sstr[0] != '\0')
	{
		if (quo_arrangement(sstr) == -1)
		{
			free(sstr);
			return (-1);
		}
	}
	free(sstr);
	return (0);
}

int	quo_order(char *tmp, t_data *data)
{
	int		i;
	int		k;
	char	*q_string;

	i = 0;
	k = 0;
	q_string = malloc((data->sqn + data->dqn + 1) * sizeof(char));
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			q_string[k++] = '\'';
		if (tmp[i] == '\"')
			q_string[k++] = '\"';
		i++;
	}
	q_string[k] = '\0';
	printf("THIS IS KK: <%i>\n", k);
	if (quo_arrangement(q_string) == -1)
	{
		free(q_string);
		return (-1);
	}
	free(q_string);
	return (0);
}

int	ft_strcpy(t_data *data, char *tmp, int len, int k)
{
	int	i;

	i = 0;
	data->array[k] = malloc((len + 1) * sizeof(char));
	if (!data->array[k])
		return (-1);
	while (i < len)
	{
		data->array[k][i] = tmp[i];
		i++;
	}
	data->array[k][i] = '\0';
	return (len);
}
