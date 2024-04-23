/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:38:42 by scely             #+#    #+#             */
/*   Updated: 2024/04/23 18:02:18 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char **str)
{
	if (ft_strncmp(*str, "echo", (int)ft_strlen("echo")) == 0)
		return (1);
	else if (ft_strncmp(*str, "cd", (int)ft_strlen("cd")) == 0)
		return (1);
	else if (ft_strncmp(*str, "env", (int)ft_strlen("env")) == 0)
		return (1);
	else if (ft_strncmp(*str, "exit", (int)ft_strlen("exit")) == 0)
		return (1);
	else if (ft_strncmp(*str, "export", (int)ft_strlen("export")) == 0)
		return (1);
	else if (ft_strncmp(*str, "pwd", (int)ft_strlen("pwd")) == 0)
		return (1);
	else if (ft_strncmp(*str, "unset", (int)ft_strlen("unset")) == 0)
		return (1);
	return (0);
}

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

t_cmds	*ft_lstnew_cmd(char **cmd, t_file *in, t_file *out)
{
	t_cmds	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->file_in = in;
	new->file_out = out;
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
	return (new);
}

t_file *ft_lstnew_file(char *file, int redirec)
{
	t_file *new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->file = ft_strdup(file);
	if (!new->file)
		return (free(new), NULL);
	new->redirec = redirec;
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

t_cmds *create_node(t_token *tmp)
{
	t_cmds *cmds;
	t_file *tmp_in;
	t_file *tmp_out;
	char *command = "\0";
	char *separateur = "\a";

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	// if (tmp == end)
	// 	return (NULL);
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			command = ft_strjoin(command, tmp->str);
			command = ft_strjoin(command, separateur);
		}
		else if (tmp->token == GREAT || tmp->token == DGREAT)
		{
			tmp_out = ft_lstnew_file(tmp->next->str, tmp->token);
			ft_lstadd_back_file(&cmds->file_out, tmp_out);
			tmp = tmp->next;
		}
		else if (tmp->token == LESS || tmp->token == HERE_DOC)
		{
			tmp_in = ft_lstnew_file(tmp->next->str, tmp->token);
			ft_lstadd_back_file(&cmds->file_in, tmp_in);
			tmp = tmp->next;	
		}
		tmp = tmp->next;
	}
	cmds->cmd = ft_split(command, *separateur);	
	printf("cmd[0] = %s\n", cmds->cmd[0]);
	printf("cmd[1] = %s\n", cmds->cmd[1]);
	return (cmds);
}

t_cmds *build_cmd(t_token *token)
{
	t_cmds *cmds;

	cmds = NULL;
	cmds = create_node(token);
	return (cmds);
}