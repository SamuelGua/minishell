/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:51:46 by scely             #+#    #+#             */
/*   Updated: 2024/05/01 11:41:47 by scely            ###   ########.fr       */
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
	if (cmd->cmd[0][0] == '\0')
		return(cmd->cmd[0]);
	if (!cmd->cmd)
		return (printf("no cmd\n"), NULL);
	new = ft_strdup(cmd->cmd[0]);
	if (!new)
		return (printf("Error malloc\n"), NULL);
	while (access(new, X_OK) && path && path[i])
	{
		free(new);
		new = ft_strjoin(path[i], cmd->cmd[0]);
		if (!new)
			return (free(cmd->cmd[0]), printf("Error malloc\n"), NULL);
		i++;
	}
	if (access(new, X_OK))
	{
		(ft_putstr_fd("bash: ", 2), ft_putstr_fd(cmd->cmd[0], 2), free(new));
		free(cmd->cmd[0]);
		return (ft_putstr_fd(" : command not found\n", 2), NULL);
	}
	return (free(cmd->cmd[0]), new);
}

int redirection(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec->cmds->file && i != -1)
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

char **build_envp(t_env *env)
{
	t_env	*tmp;
	char	**env_double;
	int	i;

	tmp = env;
	i = 0;
	while (tmp)
		(i++,tmp = tmp->next);
	env_double = malloc(sizeof(char *) * (i + 1));
	env_double[i] = NULL;
	tmp = env;
	i = 0;
	while (tmp)
	{
		env_double[i] = ft_strjoin(tmp->cle, "=");
		env_double[i] = ft_free_strjoin(env_double[i], tmp->params);
		tmp = tmp->next;
		i++;
	}
	return (env_double);
}

void child_process(t_exec *exec, char **path)
{
	close(exec->pipe[0]);
	if (redirection(exec) == -1)
		exit(1);
	exec->cmds->cmd[0] = valid_cmd(exec->cmds, path);
	ft_free(path);
	if (!exec->cmds->cmd[0])
	{
		// ne fonctionne pas pour plusieurs arguments dans le tableau
		ft_free_cmd(exec->cmds);
		close(exec->pipe[1]);
		exit(127);
	}
	exec->exec_envp = build_envp(exec->env);
	execve(exec->cmds->cmd[0], exec->cmds->cmd, exec->exec_envp);
	ft_free(exec->exec_envp);
	perror("");
	close(exec->pipe[1]);
	exit(1);
}

void execution(t_exec *exec)
{
	char **path;
	int 	pid;

	path = find_path(exec->env);
	exec->nb_pipe = nb_pipe(exec->cmds);
	if (is_builtin(exec->cmds->cmd) && exec->nb_pipe == 1)
	{
		int dup_in = dup(STDIN_FILENO);
		int dup_out = dup(STDOUT_FILENO);
		built_redir(exec);
		builtin(exec);
		dup2(dup_out, STDOUT_FILENO);
		dup2(dup_in, STDIN_FILENO);
		ft_free_cmd(exec->cmds);
		return ;
	}
	exec->previous_fd = -1;
	while (exec->nb_pipe--)
	{
		if (pipe(exec->pipe) == -1)
		{
			perror("PIPE ERROR");
			return ;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("FORK ERROR");
			return ;
		}
		if (pid == 0)
			child_process(exec, path);
		exec->cmds = exec->cmds->next;
		if (exec->previous_fd != -1)
			close(exec->previous_fd);
		exec->previous_fd = exec->pipe[0];
		close(exec->pipe[1]);
	}
	close(exec->previous_fd);
	wait_childs(pid);
}
