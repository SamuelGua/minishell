/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:51:46 by scely             #+#    #+#             */
/*   Updated: 2024/04/25 19:21:50 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	wait_childs(int pid)
{
	int	wstatus;
	int	code;

	while (errno != ECHILD)
		if (wait(&wstatus) == pid && WIFEXITED(wstatus))
			code = WEXITSTATUS(wstatus);
	if (pid == -1)
		return (127);
	return (code);
}

int	nb_pipe(t_cmds *cmds)
{
	int	i;
	t_cmds *tmp;

	tmp = cmds;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**find_path(t_env *env)
{
	char **path;
	int i;

	i = 0;
	while (env && ft_strcmp(env->cle, "PATH") != 0)
		env = env->next;
	if (!env)
		return (NULL);
	path = ft_split(env->params, ':');
	while (path[i])
	{
		path[i] = ft_free_strjoin(path[i], "/");
		i++;
	}
	return (path);
}

char *valid_cmd(t_cmds *cmd, char **path)
{
	char *new;
	int i;

	i = 0;
	if (!cmd->cmd)
		return (printf("no cmd\n"), NULL);
	new = ft_strdup(cmd->cmd[0]);
	if (!new)
		return (printf("Error malloc\n"), NULL);
	while (access(new, X_OK) && path && path[i])
	{
		free(new);
		new = ft_free_strjoin(path[i], cmd->cmd[0]);
		if (!new)
			return (printf("Error malloc\n"), NULL);
		i++;
	}
	if (path)
		free(path);
	if (access(new, X_OK))
	{
		free(new);
		// RETURN NULL ou la commande ?
		return (printf("bash: %s : command not found\n", cmd->cmd[0]), NULL);
	}
	return (free(cmd->cmd[0]), new);
}

int redirection(t_exec *exec)
{
	int	i;

	while (exec->cmds->file->next)
	{
		if (exec->cmds->file->redirec == GREAT
			|| exec->cmds->file->redirec == DGREAT)
			i = fd_out(exec->cmds->file);
		else if (exec->cmds->file->redirec == LESS)
			i = fd_in(exec->cmds->file);
		else if (exec->cmds->file->redirec == PIPE)
			i = fd_pipe(exec->cmds->file, exec);
		exec->cmds->file = exec->cmds->file->next;
	}
	return (i);
}

void child_process(t_exec *exec, char **path)
{
	if (redirection(exec))
		exit(1);
	exec->cmds->cmd[0] = valid_cmd(exec->cmds, path);
	if (!exec->cmds->cmd)
		exit (127);
	execve(exec->cmds->cmd[0], exec->cmds->cmd, NULL);
}

void execution(t_exec *exec)
{
	char **path;
	int 	pid;

	path = find_path(exec->env);
	exec->nb_pipe = nb_pipe(exec->cmds);
	while (exec->nb_pipe--)
	{
		if (pipe(exec->pipe) == -1)
		{
			perror("PIPE ERROR");
			return ;
		}
		pid = fork();
		if (pid < -1)
		{
			perror("FORK ERROR");
			return ;
		}
		if (pid == 0)
			child_process(exec, path);
		exec->cmds = exec->cmds->next;
		close(exec->pipe[0]);
		close(exec->pipe[1]);
	}
	wait_childs(pid);
}