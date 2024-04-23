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







t_cmds *create_node(t_token *tmp, t_token *end)
{
	t_cmds *cmds;
	t_file *in;
	t_file *out;
	char *command;
	char *separateur = "\a";

	if (tmp == end)
		return (NULL);
	while (tmp != end)
	{
		if (tmp->token == WORD)
		{
			command = ft_strjoin(command, tmp->str);
			command = ft_strjoin(command, separateur);
		}
		else if (tmp->token == GREAT && tmp->token == DGREAT)
		{
			out->file = tmp->str;
			out->redirec = tmp->type;
			// faire la suite
		}
	}
}

t_cmds *build_cmd(t_token *token)
{
	t_cmds *cmds;
	t_token *tmp;

	cmds = NULL;
	while (token)
	{
		tmp = token;
		while (token && token->type != PIPE)
			token = token->next;
		cmds = create_node(tmp, token);
		token = token->next;
	}
	return (cmds);
}