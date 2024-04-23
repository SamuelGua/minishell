/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:18:40 by scely             #+#    #+#             */
/*   Updated: 2024/04/22 15:03:11 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gerer les newline
int	check_whitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	close_quoted(char *str)
{
	int	i;
	int	quoted;

	i = 0;
	quoted = 0;
	while (str[i])
	{
		quoted = is_quoted(quoted, str[i]);
		i++;
	}
	return (quoted);
}

int	good_operator(t_token *token)
{
	if (token->type == WORD || token->next)
		return (0);
	if (token->type == PIPE && token->token == OPERATOR)
		return (0);
	else
		return (1);
}

int	is_valid_token(t_token *token)
{
	if (token->type == PIPE)
		return (printf("bash: syntax error near unexpected token"), 2);
	while (token)
	{
		if (close_quoted(token->str) || good_operator(token))
		{
			free_token(token);
			return (printf("bash: syntax error near unexpected token\n"), 2);
		}
		token = token->next;
	}
	return (0);
}
