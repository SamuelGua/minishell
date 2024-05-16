/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 12:47:10 by scely             #+#    #+#             */
/*   Updated: 2024/05/16 21:33:22 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printmsgerr(t_exec *exec)
{
	char	*error_message;

	error_message = ft_strjoin("minishell: ", exec->cmds->cmd[0]);
	if (!error_message)
		return (perror("minishell: "));
	perror(error_message);
	free(error_message);
}

int	check_isfile(t_exec *exec)
{
	struct stat	fileinfo;

	if (exec->cmds->cmd[0][0] == '\0')
		return (127);
	if (ft_strchr(exec->cmds->cmd[0], '/'))
	{
		if (stat(exec->cmds->cmd[0], &fileinfo) == -1)
			return (printmsgerr(exec), 127);
		if (access(exec->cmds->cmd[0], X_OK))
			return (printmsgerr(exec), 126);
		else if (S_ISDIR(fileinfo.st_mode))
		{
			print_message("mini: ", exec->cmds->cmd[0], ": Is a directory", 2);
			return (126);
		}
	}
	return (-1);
}

int	valid_cmd(t_exec *exec, char **path)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strdup(exec->cmds->cmd[0]);
	if (!new)
		return (ft_putstr_fd("Error malloc\n", 2), 2);
	while (access(new, X_OK) && path && path[i])
	{
		free(new);
		new = ft_strjoin(path[i], exec->cmds->cmd[0]);
		if (!new)
			return (ft_putstr_fd("Error malloc\n", 2), 2);
		i++;
	}
	if (access(new, X_OK))
	{
		print_message("minishell: ", exec->cmds->cmd[0],
			" : command not found", 2);
		return (free(new), 127);
	}
	free(exec->cmds->cmd[0]);
	exec->cmds->cmd[0] = new;
	return (0);
}

int	check_errors(t_exec *exec, char **path)
{
	int	i;

	i = -1;
	close(exec->pipe[0]);
	if (redirection(exec) == -1)
		return (1);
	else if (!exec->cmds->cmd[0])
		return (0);
	else if (is_builtin(exec->cmds->cmd))
	{
		if (path)
			ft_free(path);
		builtin(exec, NULL, 0);
		return (0);
	}
	i = check_isfile(exec);
	if (i > 0)
		return (i);
	else if (valid_cmd(exec, path) || !exec->cmds->cmd[0])
		return (127);
	return (i);
}
