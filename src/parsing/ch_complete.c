/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_complete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:19:54 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/15 12:19:56 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*int	word_counter(const char *str)
{
	int	count;
	int	in_word;
	int	in_quotes;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	while (*str)
	{
		ft_word_itter(str, &in_quotes, &in_word, &count);
		str++;
	}
	return (count);
}*/

int	var_finder(char **env, char *s)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (f_strcmp(env[i], s) != -1)
			return (i); 
		i++;
	}
	return (-1);
}

char	*str_modifier(char *str, char *var, int d)
{
	int		eq;
	int		i;
	char	*tmp;

	i = 0;
	eq = f_strchr(var, '=') + 1;
	tmp = malloc((f_strlen(var + eq) + d + 1) * sizeof(char));
	while (i < d)
	{
		tmp[i] = str[i];
		i++;
	}
	while (var[eq] != '\0')
	{
		tmp[i] = var[eq];
		i++;
		eq++;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

int	expansion(t_data *data, char **env)
{
	int	i;
	int	d;
	int	v;

	i = 0;
	while (data->array[i] != NULL)
	{
		d = f_strchr(data->array[i], '$');
		if (d != -1 && (f_strchr(data->array[i], '\'') == -1))
		{
			v = var_finder(env, data->array[i] + d + 1);
			if (v == -1)
				return (-1);
			data->array[i] = str_modifier(data->array[i], env[v], d);
			if (data->array[i] == NULL)
				return (-1);
		}
		i++;
	}
	return (0);
}

char	**input_validation(char *tmp, char **env)
{
	t_data	*data;
	char	**arr;

	data = malloc(sizeof(t_data));
	//arr = (char**)malloc(sizeof(char*));
	if (quo_num(tmp, data) == -1)
		return (NULL);
	data->word_count = word_counter(tmp);
	if (data->word_count == 0)
		return (NULL);
	if (data->sqn + data->dqn > 0)
		if (quo_order(tmp, data) == -1)
			return (NULL);
	data->array = (char **)malloc((data->word_count + 4) * sizeof(char *));
	if (ft_chopper(data, tmp, 0) == -1)
		return (NULL);
	if (expansion(data, env) == -1)
		return (NULL);
	arr = data->array;
	free(data);
	return (arr);
}
/*
int	main(int ac, char **av, char **env)
{
	int	i = 0;
	char	*tmp;
	char	**array;
	if (ac && av)
	read_history("history_file");
	tmp = readline("promp> ");
	if ((array = input_validation(tmp, env)) == NULL)
	{
		printf("wrong input you goofy");
		return (0);
	}
	while (array[i] != NULL)
	{
		printf("<%s>\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}*/					// finally fixed, but should do one last test!!!
