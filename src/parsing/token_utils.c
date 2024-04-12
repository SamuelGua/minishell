/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 10:22:41 by scely             #+#    #+#             */
/*   Updated: 2024/04/12 12:17:21 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_lstnew_token(char *str, int len, int type, int token)
{
	t_token *node;

	node = malloc(sizeof(t_token));
	if(!node)	
		return (NULL);
	node->str = malloc(sizeof(char) * len + 1);
	ft_strlcpy(node->str, str, len + 1);
	node->type  = type;
	node->token = token;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_token(t_token **token, t_token *node)
{
	t_token *tmp;

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
