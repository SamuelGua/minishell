/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:22:41 by scely             #+#    #+#             */
/*   Updated: 2024/05/03 20:28:07 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lstnew_token(char *str, int len, int type, int token)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->str = malloc(sizeof(char) * len + 1);
	if (!node->str)
		return (NULL);
	ft_strlcpy(node->str, str, len);
	node->type = type;
	node->token = token;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_token(t_token **token, t_token *node)
{
	t_token	*tmp;

	tmp = *token;
	if (!*token)
		*token = node;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
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

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}

void	value_pars_init(t_parsutils *utils_pars)
{
	utils_pars->i = 0;
	utils_pars->quoted = NO_QUOTE;
	utils_pars->len = 1;
	utils_pars->type_token = 0;
	utils_pars->start_token = 0;
	utils_pars->sous_type = 1;
}
