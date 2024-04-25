/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:18:40 by scely             #+#    #+#             */
/*   Updated: 2024/04/25 19:20:19 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **str)
{
	if (ft_strncmp(*str, "echo", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "cd", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "env", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "exit", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "export", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "pwd", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "unset", (int)ft_strlen(*str)) == 0)
		return (1);
	return (0);
}

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

// operateur de controle  peut etre suivi par un operateur
// operateur suivi d'un mot
// quote pas ferme
int	good_operator(t_token *token)
{
	if (token->type == WORD)
		return (0);
	else if (token->token == PIPE && token->next && token->next->token != PIPE
		&& (token->next->type == OPERATOR || token->next->type == WORD))
		return (0);
	else if (token->type == OPERATOR && token->next
		&& token->next->type == WORD)
		return (0);
	else
		return (1);
}

// error sortie 2 ou 1 || ft_putstr
int	is_valid_token(t_token *token)
{
	if (token->token == PIPE)
	{
		printf("minishell: syntax error near unexpected token");
		printf(" « %s »\n", token->str);
		return (free_token(token), 2);
	}
	while (token)
	{
		if (close_quoted(token->str) || good_operator(token))
		{
			printf("minishell: syntax error near unexpected token");
			printf(" « %s »\n", token->str);
			return (free_token(token), 2);
		}
		token = token->next;
	}
	return (0);
}
