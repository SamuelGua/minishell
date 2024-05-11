/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:38:42 by scely             #+#    #+#             */
/*   Updated: 2024/05/11 11:57:25 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_init(t_file *tmp_file, t_token *end, t_cmds *cmds, int i)
{
	tmp_file = ft_lstnew_file(end->str, end->token);
	tmp_file->pipe = i;
	ft_lstadd_back_file(&cmds->file, tmp_file);
}

char	**node_init(t_token *tmp, t_file *file, t_cmds *cmds, t_build_cmd *utl)
{
	char	**command;
	int		i;

	i = cmds_size(tmp, utl->end);
	command = malloc(sizeof(char *) * (i + 1));
	if (!command)
		return (NULL);
	i = 0;
	while (tmp != utl->end)
	{
		if (tmp->type == WORD)
			command[i++] = ft_strdup(tmp->str);
		else if (tmp->token >= GREAT && tmp->token < PIPE)
		{
			file = ft_lstnew_file(tmp->next->str, tmp->token);
			if (!file)
				return (NULL);
			(ft_lstadd_back_file(&cmds->file, file), set_nbs(tmp, file, utl));
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	command[i] = NULL;
	return (command);
}

// 0 pour pas dans le here_doc || 1 pour dans le here_doc
int	clean_token(t_exec *exec)
{
	t_token	*tmp;
	t_token	*head;

	head = exec->token;
	tmp = exec->token;
	while (exec->token)
	{
		if (tmp->token != HERE_DOC)
		{
			exec->token->str = expansion(exec->token->str, exec, 0);
			if (exec->token->str == NULL)
				return (1);
			exec->token->str = delete_quote(exec->token->str);
			if (exec->token->str == NULL)
				return (1);
		}
		tmp = exec->token;
		exec->token = exec->token->next;
	}
	if (!head->str[0])
		exec->token = head->next;
	else
		exec->token = head;
	return (0);
}

t_cmds	*build_cmd(t_exec *exec)
{
	t_build_cmd	utils;

	utils.cmds = NULL;
	utils.tmp = exec->token;
	utils.nb_here_doc = 0;
	if (clean_token(exec))
		return (free_token(utils.tmp), NULL);
	while (exec->token)
	{
		utils.end = exec->token->next;
		while (utils.end && utils.end->token != PIPE)
			utils.end = utils.end->next;
		utils.cmds_tmp = create_node(exec->token, &utils);
		ft_lstadd_back_cmd(&utils.cmds, utils.cmds_tmp);
		exec->token = utils.end;
	}
	free_token(utils.tmp);
	return (utils.cmds);
}
