/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:38:42 by scely             #+#    #+#             */
/*   Updated: 2024/05/02 10:06:34 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_build_cmd
{
	t_cmds	*cmds_tmp;
	t_token	*end;
	t_cmds	*cmds;
	t_token	*tmp;
	int		nb_here_doc;
} t_build_cmd;


void	print_lst_cmd(t_cmds *cmd)
{
	int	i;
	t_cmds *tmp = cmd;

	i = -1;
	if (tmp->type == 0)
		printf("commandes\n");
	else if (tmp->type == 1)
		printf("built-in\n");
	else 
		printf("none tmps\n");
	while (tmp->cmd[++i])
		printf("cmd[%d] = %s\n", i, tmp->cmd[i]);
	if (tmp->file)
		printf("\033[1;31mFile [ \033[0m");
	while (tmp->file)
	{
		printf("file = %s ** redirec = %d\t", tmp->file->file, tmp->file->redirec);
		if (tmp->file->redirec == HERE_DOC)
			printf("{%d}", tmp->file->n_heredoc);
		else if (tmp->file->redirec == PIPE)
			printf("{%d}", tmp->file->pipe);
		tmp->file = tmp->file->next;
		if (!tmp->file)
			printf("\033[1;31m]\n\033[0m");
	}
}

void	pipe_init(t_file *tmp_file, t_token *end, t_cmds *cmds, int i)
{
	tmp_file = ft_lstnew_file(end->str, end->token);
	tmp_file->pipe = i;
	ft_lstadd_back_file(&cmds->file, tmp_file);
}
int cmds_size(t_token *tmp, t_token *end)
{
	int	i;

	i = 0;
	while (tmp != end)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**node_init(t_token *tmp, t_token *end, t_file *tmp_file, t_cmds *cmds)
{
	char	**command;
	int		i;
	int 	nb_here;
	
	nb_here = 0;
	i = cmds_size(tmp, end);
	command = malloc(sizeof(char *) * (i + 1));
	if (!command)
		return (NULL);
	i = 0;
	while (tmp != end)
	{
		if (tmp->type == WORD)
			command[i++] = ft_strdup(tmp->str);
		else if (tmp->token >= GREAT && tmp->token < PIPE) // || OU &&
		{
			tmp_file = ft_lstnew_file(tmp->next->str, tmp->token);
			ft_lstadd_back_file(&cmds->file, tmp_file);
			if (tmp->token == HERE_DOC)
			{
				tmp_file->n_heredoc = nb_here;
				nb_here++;
			}
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	command[i] = NULL;
	return (command);
}

t_cmds	*create_node(t_token *tmp, t_token *end)
{
	t_cmds	*cmds;
	t_file	*tmp_file;

	tmp_file = NULL;
	cmds = malloc(sizeof(t_cmds));
	if (!cmds)
		return (NULL);
	cmds->file = NULL;
	if (end && end->token == PIPE)
		pipe_init(tmp_file, end, cmds, 1);
	if (tmp && tmp->token == PIPE)
		(pipe_init(tmp_file, tmp, cmds, 0), tmp = tmp->next);
	cmds->cmd = node_init(tmp, end, tmp_file, cmds);
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
	// t_cmds	*cmds_tmp;
	// t_token	*end;
	// t_cmds	*cmds;
	// t_token	*tmp;
	// int		nb_here_doc;

	t_build_cmd utils;
	utils.cmds = NULL;
	utils.tmp = token;
	utils.nb_here_doc = 0;
	clean_token(token, env);
	while (token)
	{
		utils.end = token->next;
		while (utils.end && utils.end->token != PIPE)
			utils.end = utils.end->next;
		utils.cmds_tmp = create_node(token, utils.end);
		ft_lstadd_back_cmd(&utils.cmds, utils.cmds_tmp);
		token = utils.end;
	}
	free_token(utils.tmp);
	return (utils.cmds);
}
