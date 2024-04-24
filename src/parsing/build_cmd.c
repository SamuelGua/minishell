/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:38:42 by scely             #+#    #+#             */
/*   Updated: 2024/04/24 15:29:27 by scely            ###   ########.fr       */
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
	new->next = NULL;
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

void print_lst_cmd(t_cmds *cmd)
{
	int i;

	i = -1;
	while (cmd->cmd[++i])
		printf("cmd[%d] = %s\n", i, cmd->cmd[i]);
	if (cmd->file_out)
		printf("\033[1;31mFile out [ \033[0m");
	while (cmd->file_out)
	{
		printf("file = %s ** redirec = %d\t", cmd->file_out->file, cmd->file_out->redirec);
		cmd->file_out = cmd->file_out->next;
		if (!cmd->file_out)
			printf("\033[1;31m]\n\033[0m");
	}
	if (cmd->file_in)
		printf("\033[1;32mFile in  [ \033[0m");
	while (cmd->file_in)
	{
		printf("file = %s ** redirec = %d\t", cmd->file_in->file, cmd->file_in->redirec);
		cmd->file_in = cmd->file_in->next;
		if (!cmd->file_in)
			printf("\033[1;32m]\n\033[0m");
	}
}

t_cmds *create_node(t_token *tmp, t_token *end)
{
	t_cmds *cmds = NULL;
	t_file *tmp_in =  NULL;
	t_file *tmp_out =  NULL;
	char *command = "\0";
	char *separateur = "\a";

	cmds = malloc(sizeof(t_cmds));
	cmds->file_in = NULL;
	cmds->file_out = NULL;
	if (!cmds)
		return (NULL);
	if (end && end->token == PIPE)
	{
		tmp_out = ft_lstnew_file(end->next->str, end->token);
		ft_lstadd_back_file(&cmds->file_out, tmp_out);
	}
	else if (tmp && tmp->token == PIPE)
	{
		tmp_in = ft_lstnew_file(tmp->next->str, tmp->token);
		ft_lstadd_back_file(&cmds->file_in, tmp_in);
		tmp = tmp->next;
	}
	while (tmp && tmp->token != PIPE)
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
	cmds->next = NULL;
	// t_cmds *test = cmds;
	// while (test)
	// {
	// 	print_lst_cmd(test);	
	// 	test = test->next;
	// }
	return (cmds);
}

t_cmds *build_cmd(t_token *token)
{
	t_cmds *cmds_tmp;
	t_cmds *cmds = NULL;
	t_token *end ;

	while (token)
	{
		end = token->next;
		while (end && end->token != PIPE)
			end = end->next;
		cmds_tmp = create_node(token, end);
		print_lst_cmd(cmds_tmp);
		ft_lstadd_back_cmd(&cmds, cmds_tmp);
		token = end;
	}
	return (cmds);
}