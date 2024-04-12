/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:14:53 by scely             #+#    #+#             */
/*   Updated: 2024/04/12 12:57:26 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	if (c == '>' || c == '<' || c == '&' || c == '|')
		return (1);
	return (0);
}

int check_operator(char *str, int *len)
{
	int i;

	i = 0;
	if (!ft_strncmp(str, ">>", 2) || !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, "&&", 2) || !ft_strncmp(str, "||", 2) )
	{
		*len = 2;
		return (1);
	}
	*len = 1;
	return (1);

}

void	print_token(t_token *token)
{
	printf("token\ttype\tstr\n");
	while (token)
	{
		printf("%d\t", token->type);
		printf("%d\t", token->token);
		printf("%s\n", token->str);
		token = token->next;
	}
}
void free_token(t_token *token)
{
	t_token *tmp;
	while(token)
	{
		tmp = token;
		token = token->next;
		free(tmp);
	}
}

t_token	*init_token(char *prompt)
{
	int	i;
	int	len;
	t_token *token = NULL;
	t_token *node = NULL;

	i = 0;
	while(prompt[i])
	{
		len = 0;
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] && is_operator(prompt[i]))
		{
			if (check_operator(&prompt[i], &len))
			{
				i += len;
				node = ft_lstnew_token(&prompt[i - len], len, OPERATOR, 0);
				//token operator
			}
		}
		else if (prompt[i] == '\'')
		{
			(len++, i++); // 1er quote
			while (prompt[i] && prompt[i] != '\'')
				(len++, i++);
			(len++, i++);// 2eme quote
			printf("len %d, i %d (%d)\n", len, i, i-len);
			node = ft_lstnew_token(&prompt[i - len], len, WORD, QUOTED);
		}
		else if (prompt[i] == '\"')
		{
			(len++, i++);
			while (prompt[i] && prompt[i] != '\"')
				(len++, i++);
			(len++, i++);
			node = ft_lstnew_token(&prompt[i - len], len, WORD, QUOTED);
		}
		else 
		{
			while (prompt[i] && is_operator(prompt[i]) == 0 && prompt[i] != ' ')
				(len++, i++);
			printf("len %d, i %i\n", len, i);
			node = ft_lstnew_token(&prompt[i - len], len, WORD, UNQUOTED);
			if (prompt[i] == ' ')
				i++;
		}
		ft_lstadd_back_token(&token, node);
	}
	return (token);
}
