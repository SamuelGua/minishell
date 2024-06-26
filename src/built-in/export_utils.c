/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:40:50 by scely             #+#    #+#             */
/*   Updated: 2024/05/03 23:21:25 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_export(t_export *export)
{
	if (export)
	{
		ft_free_export(export->left);
		ft_free_export(export->right);
		free(export->cle);
		free(export->params);
		free(export);
	}
}

static	t_export	*ft_lstnew_export(char *cle, char *params)
{
	t_export	*new;

	new = malloc(sizeof(t_export));
	if (!new)
		return (NULL);
	new->cle = ft_strdup(cle);
	if (!new->cle)
		return (free(new), NULL);
	new->params = ft_strdup(params);
	if (!new->params)
		return (free(new->cle), free(new), NULL);
	new->left = NULL;
	new->right = NULL;
	return (new);
}

static	void	insert_export(t_export **list, t_export *node)
{
	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	if (ft_strcmp((*list)->cle, node->cle) > 0)
		insert_export(&(*list)->left, node);
	else
		insert_export(&(*list)->right, node);
}

t_export	*init_export(t_env *env)
{
	t_export	*tmp;
	t_export	*export;

	export = NULL;
	if (env == NULL)
		return (NULL);
	while (env)
	{
		tmp = ft_lstnew_export(env->cle, env->params);
		if (!tmp)
			return (ft_free_export(export), NULL);
		insert_export(&export, tmp);
		env = env->next;
	}
	return (export);
}
