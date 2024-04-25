/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:38:42 by scely             #+#    #+#             */
/*   Updated: 2024/04/25 19:26:35 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lst_cmd(t_cmds *cmd)
{
	int	i;

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

void	pipe_init(t_file *tmp_file, t_token *end, t_cmds *cmds, int i)
{
	tmp_file = ft_lstnew_file(end->str, end->token);
	tmp_file->pipe = i;
	ft_lstadd_back_file(&cmds->file, tmp_file);
}

char	*node_init(t_token *tmp, t_token *end, t_file *tmp_file, t_cmds *cmds)
{
	char	*command;

	command = malloc(sizeof(char));
	command[0] = '\0';
	while (tmp != end)
	{
		if (tmp->type == WORD)
		{
			command = ft_free_strjoin(command, tmp->str);
			command = ft_free_strjoin(command, "\a");
		}
		else if (tmp->token >= GREAT || tmp->token < PIPE)
		{
			tmp_file = ft_lstnew_file(tmp->next->str, tmp->token);
			ft_lstadd_back_file(&cmds->file, tmp_file);
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	return (command);
}

t_cmds	*create_node(t_token *tmp, t_token *end)
{
	t_cmds	*cmds;
	t_file	*tmp_file;
	char	*command;

	tmp_file = NULL;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->file = NULL;
	if (end && end->token == PIPE)
		pipe_init(tmp_file, end, cmds, 0);
	if (tmp && tmp->token == PIPE)
		(pipe_init(tmp_file, tmp, cmds, 1), tmp = tmp->next);
	command = node_init(tmp, end, tmp_file, cmds);
	if (command[0])
		cmds->cmd = ft_split(command, 7);
	else
		cmds->cmd = ft_split("none", 7);
	cmds->type = is_builtin(cmds->cmd);
	cmds->next = NULL;
	return (cmds);
}

void	clean_token(t_token *token, t_env *env)
{
	t_token	*tmp;

	tmp = token;
	while (token)
	{
		token->str = expansion(token->str, env);
		if (tmp->type != HERE_DOC)
			token->str = delete_quote(token->str);
		tmp = token;
		token = token->next;
	}
}

t_cmds	*build_cmd(t_token *token, t_env *env)
{
	t_cmds	*cmds_tmp;
	t_token	*end;
	t_cmds	*cmds;

	cmds = NULL;
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
