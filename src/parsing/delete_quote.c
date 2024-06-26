/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:23:31 by scely             #+#    #+#             */
/*   Updated: 2024/05/15 11:06:33 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(int quoted, char c)
{
	if (quoted == NO_QUOTE && c == '\'')
		return (S_QUOTE);
	else if (quoted == NO_QUOTE && c == '\"')
		return (D_QUOTE);
	else if (quoted == S_QUOTE && c == '\'')
		return (NO_QUOTE);
	else if (quoted == D_QUOTE && c == '\"')
		return (NO_QUOTE);
	return (quoted);
}

void	quote_check(char *c, char stri)
{
	if (*c == '\0' && stri == '\'')
		*c = '\'';
	else if (*c == '\0' && stri == '\"')
		*c = '\"';
	else if (*c == stri && stri == '\'')
		*c = '\0';
	else if (*c == stri && stri == '\"')
		*c = '\0';
}

char	*clean_quote(char *str)
{
	char	c;
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str)) + 1);
	if (!new)
		return (NULL);
	c = '\0';
	while (str[i])
	{
		if (c == str[i] || ((str[i] == '\'' || str[i] == '\"') && c == '\0'))
			(quote_check(&c, str[i]), i++);
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
		new[j] = '\0';
	}
	return (free(str), new);
}

char	*delete_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (clean_quote(str));
		i++;
	}
	return (str);
}
