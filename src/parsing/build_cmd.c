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
	if (ft_strncmp(*str, "echo", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "cd", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "env", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "exit", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "export", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "pwd", (int)ft_strlen(*str)) == 0)
		return (1);
	else if (ft_strncmp(*str, "unset", (int)ft_strlen(*str)) == 0)
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
	if (cmd->type == 0)
		printf("commandes\n");
	else
		printf("built-in\n");
	while (cmd->cmd[++i])
		printf("cmd[%d] = %s\n", i, cmd->cmd[i]);
	if (cmd->file)
		printf("\033[1;31mFile out [ \033[0m");
	while (cmd->file)
	{
		printf("file = %s ** redirec = %d\t", cmd->file->file, cmd->file->redirec);
		if (cmd->file->redirec == PIPE)
			printf("{%d}", cmd->file->pipe);
		cmd->file = cmd->file->next;
		if (!cmd->file)
			printf("\033[1;31m]\n\033[0m");
	}
}

t_cmds *create_node(t_token *tmp, t_token *end)
{
	t_cmds *cmds = NULL;
	t_file *tmp_file =  NULL;
	char *command = "\0";
	char *separateur = "\a";

	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->file = NULL;
	if (end && end->token == PIPE)
	{
		tmp_file = ft_lstnew_file(end->next->str, end->token);
		tmp_file->pipe = 0;
		ft_lstadd_back_file(&cmds->file, tmp_file);
	}
	if (tmp && tmp->token == PIPE)
	{
		tmp_file = ft_lstnew_file(tmp->str, tmp->token);
		tmp_file->pipe = 1;
		ft_lstadd_back_file(&cmds->file, tmp_file);
		tmp = tmp->next;
	}
	while (tmp != end)
	{
		// delete quote et expand
		if (tmp->type == WORD)
		{
			command = ft_strjoin(command, tmp->str);
			command = ft_strjoin(command, separateur);
		}
		else if (tmp->token >= GREAT || tmp->token < PIPE)
		{
			tmp_file = ft_lstnew_file(tmp->next->str, tmp->token);
			ft_lstadd_back_file(&cmds->file, tmp_file);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	cmds->cmd = ft_split(command, *separateur);
	cmds->type = is_builtin(cmds->cmd);
	cmds->next = NULL;
	return (cmds);
}
void clean_token(t_token *token, t_env *env)
{
	(void)env;

	t_token *tmp = token;
	while (token)
	{
		token->str = expansion(token->str, env);
		if (tmp->type != HERE_DOC)
			token->str = delete_quote(token->str);
		tmp = token;
		token = token->next;
	}
}

t_cmds *build_cmd(t_token *token, t_env *env)
{
	t_cmds *cmds_tmp;
	t_cmds *cmds = NULL;
	t_token *end;
	(void)env;

	clean_token(token, env);
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
// cd | echo | ls