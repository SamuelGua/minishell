/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:14:53 by scely             #+#    #+#             */
/*   Updated: 2024/04/12 17:45:07 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define NO_QUOTE 0
#define QUOTE 1
#define D_QUOTE 2

int	is_operator(char c, int stats)
{
	if (stats)
		return (0);
	if (c == '>' || c == '<' || c == '&' || c == '|'|| c == '('|| c == ')')
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

int value_operator(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (DGREAT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (OR_IF);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (AND_IF);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (LESS);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (GREAT);
	else if (ft_strncmp(str, "(", 1) == 0)
		return (LBRAKET);
	else if (ft_strncmp(str, ")", 1) == 0)
		return (RBRAKET);
	return (666);
}

t_token	*init_token(char *prompt)
{
	int	i;
	int	len;
	t_token *token = NULL;
	t_token *node = NULL;
	int		quoted = NO_QUOTE;

	i = 0;
	while(prompt[i] && prompt[i] != '#')
	{
		len = 0;
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] && is_operator(prompt[i], quoted))
		{
			if (check_operator(&prompt[i], &len))
			{
				i += len;
				node = ft_lstnew_token(&prompt[i - len], len, OPERATOR, value_operator((&prompt[i - len])));
				//token operator
			}
		}
		else if (prompt[i] == '\'')
		{	//single quoted
			quoted = QUOTE;
			(len++, i++); // 1er quote
			while (prompt[i] && is_operator(prompt[i], quoted) == 0)
			{
				if ( prompt[i] == '\'')
					quoted = NO_QUOTE;
				(len++, i++);
				if ( prompt[i] == ' ' && quoted == NO_QUOTE)
					break;
			}
			node = ft_lstnew_token(&prompt[i - len], len, WORD, QUOTED);
		}
		else if (prompt[i] == '\"')
		{	//double quoted
			(len++, i++);
			quoted = D_QUOTE;
			while (prompt[i] && is_operator(prompt[i], quoted) == 0)
			{
				if (prompt[i] == '\"')
					quoted = NO_QUOTE;
				(len++, i++);
				if ( prompt[i] == ' ' && quoted == NO_QUOTE)
					break;
				printf("quoted = %d prompt = %c len = %d\n",quoted, prompt[i], len);
			}
			node = ft_lstnew_token(&prompt[i - len], len, WORD, QUOTED);
		}
		else 
		{
			if (prompt[i] == '#')
				break;
			while (prompt[i] && is_operator(prompt[i + 1], quoted) == 0 && prompt[i] != ' ')
				(len++, i++);
			node = ft_lstnew_token(&prompt[i - len], len, WORD, UNQUOTED);
			if (prompt[i] == ' ')
				i++;
		}
		if (quoted)
		{
			printf("Prompt mal ecris\n");
			return (NULL);
		}
		ft_lstadd_back_token(&token, node);
	}
	return (token);
}
