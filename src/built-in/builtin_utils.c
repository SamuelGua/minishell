/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:33:25 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 13:11:10 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin(t_exec *exec, int *fd_origin)
{
	if (ft_strcmp(exec->cmds->cmd[0], "env") == 0)
		return (ft_env(exec->env, exec->cmds->cmd));
	else if (ft_strcmp(exec->cmds->cmd[0], "unset") == 0)
		return (ft_unset(&exec->export, &exec->env, exec->cmds->cmd));
	else if (ft_strcmp(exec->cmds->cmd[0], "echo") == 0)
		return (ft_echo(exec->cmds->cmd));
	else if (ft_strcmp(exec->cmds->cmd[0], "export") == 0)
		return (ft_export(&exec->export, &exec->env, exec->cmds->cmd, 0));
	else if (ft_strcmp(exec->cmds->cmd[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(exec->cmds->cmd[0], "exit") == 0)
		return (ft_exit(exec, fd_origin));
	else if (ft_strcmp(exec->cmds->cmd[0], "cd") == 0)
		return (ft_cd(exec->env, exec->cmds->cmd));
	return (0);
}

int	is_builtin(char **str)
{
	if (!str[0])
		return (2);
	if (ft_strcmp(*str, "echo") == 0)
		return (1);
	else if (ft_strcmp(*str, "cd") == 0)
		return (1);
	else if (ft_strcmp(*str, "env") == 0)
		return (1);
	else if (ft_strcmp(*str, "exit") == 0)
		return (2);
	else if (ft_strcmp(*str, "export") == 0)
		return (1);
	else if (ft_strcmp(*str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(*str, "unset") == 0)
		return (1);
	return (0);
}
