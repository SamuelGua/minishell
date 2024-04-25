/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 18:10:46 by scely             #+#    #+#             */
/*   Updated: 2024/04/25 18:22:21 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *node)
{
	t_cmds	*tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	else
		*lst = node;
}

t_cmds	*ft_lstnew_cmd(char **cmd, t_file *file)
{
	t_cmds	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->file = file;
	new->cmd = malloc(sizeof(cmd));
	if (!new->cmd)
		return (NULL);
	while (cmd[i])
	{
		new->cmd[i] = ft_strdup(cmd[i]);
		if (!new->cmd)
			return (NULL);
		i++;
	}
	new->next = NULL;
	return (new);
}

t_file	*ft_lstnew_file(char *file, int redirec)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->file = ft_strdup(file);
	if (!new->file)
		return (free(new), NULL);
	new->redirec = redirec;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_file(t_file **lst, t_file *node)
{
	t_file	*tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	else
		*lst = node;
}
