/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 11:38:42 by scely             #+#    #+#             */
/*   Updated: 2024/04/23 10:24:16 by scely            ###   ########.fr       */
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

t_cmds *ft_lstnew_cmd(char **cmd, int redirec, char *file, int type)
{
	
}

t_cmds *create_node(t_token *tmp, t_token *end)
{
	t_cmds cmd;
	char *
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
}