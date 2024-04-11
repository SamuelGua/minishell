/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token..c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:14:53 by scely             #+#    #+#             */
/*   Updated: 2024/04/11 18:33:36 by scely            ###   ########.fr       */
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
	ft_strlcpy(node->str, str, len);
	node->type  = type;
	node->token = token;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back_token(t_token **token, t_token *node)
{
	t_token *new;

	new = (*token);
	if (!*token)
		*token = new;
	else
	{
		while (new->next)
			new = new->next;
		new->next = node;
	}
}

// int	is_operateur(char c)
// {
// 	if (c == '')
// }

t_token	*init_token(char *prompt)
{
	int	i;
	int	len;

	i = 0;
	while(prompt[i])
	{
		
		i++;
	}
}
