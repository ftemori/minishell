/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chopper3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:56:14 by ftemori           #+#    #+#             */
/*   Updated: 2024/01/16 10:56:16 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int is_quote(char c)
{
	return (c == '"' || c == '\'');
}

int is_word_start(char *c, int in_quotes, int in_word)
{
	return ((c[0] == ' ' && !in_quotes) || is_special_char(c) || (is_quote(c[0]) && !in_word));
}

int	word_counter(char *str) {
	int	count = 1;
	int	in_quotes = 0;
	int	in_word = 0;
	int	i;

	i = 0;
	while (str[i] != '\0') {
		if (is_word_start(str + i, in_quotes, in_word)) {
			count++;
			in_word = 1;
		} else if (is_quote(str[i])) {
			in_quotes = !in_quotes;
		} else {
			in_word = 1;
		}
		i++;
	}

	return count;
}
