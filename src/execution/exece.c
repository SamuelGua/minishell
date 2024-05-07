/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:51:46 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 17:44:15 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_isfile(t_exec *exec)
{
	struct stat fileinfo;

	if (exec->cmds->cmd[0][0] == '\0')
		return(1);
	if (ft_strchr(exec->cmds->cmd[0], '/'))
	{
		if (stat(exec->cmds->cmd[0], &fileinfo) == -1)
        	return (perror("stat"), 1);
    	if (access(exec->cmds->cmd[0], X_OK))
		{
			perror("");
			return (1);
		}
		else if (S_ISDIR(fileinfo.st_mode))
		{
			print_message("minishell: ", exec->cmds->cmd[0], ": Is a directory\n", 2);
			return (1);
		}
	}
	return (0);
}

int	valid_cmd(t_exec *exec, char **path)
{
	char *new;
	int i;

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
		print_message("minishell: ", exec->cmds->cmd[0], " : command not found\n", 2);
		return (free(new), 127);
	}
	free(exec->cmds->cmd[0]);
	exec->cmds->cmd[0] = new;
	return (0);
}

int check_erros(t_exec *exec, char **path)
{
	int	i;

	i = -1;
	close(exec->pipe[0]);
	if (redirection(exec) == -1)
		i = 1;
	else if (!exec->cmds->cmd[0])
		i = 0;
	else if (is_builtin(exec->cmds->cmd))
	{
		if (is_builtin(exec->cmds->cmd) == 2 && path) 
			ft_free(path);;
		builtin(exec, NULL);
		i = 0;
	}
	else if (check_isfile(exec))
		i = 126;
	else if (valid_cmd(exec, path) || !exec->cmds->cmd[0])
		i = 127;
	return (i);
}

void child_process(t_exec *exec, char **path)
{
	int i;

	i = check_erros(exec, path);
	if (i != -1)
	{
		close(exec->pipe[1]);
		ft_free_exec(exec);
		if (path)
			ft_free(path);
		exit(i);
	}
	if (path)
		ft_free(path);
	exec->exec_envp = build_envp(exec->env);
	execve(exec->cmds->cmd[0], exec->cmds->cmd, exec->exec_envp);
	ft_free(exec->exec_envp);
	perror("");
	ft_free_exec(exec);
	close(exec->pipe[1]);
	exit(1);
}

int exec_sbuiltin(t_exec *exec)
{	
	int	j;
	int fd_orgin[2];

	fd_orgin[0] = dup(STDIN_FILENO);
	fd_orgin[1] = dup(STDOUT_FILENO);
	j = redirection (exec);
	if (j >= 0 && exec->cmds->cmd[0])
		j = builtin(exec, fd_orgin);
	dup2(fd_orgin[1], STDOUT_FILENO);
	dup2(fd_orgin[0] , STDIN_FILENO);
	close(fd_orgin[1]);
	close(fd_orgin[0] );
	ft_free_cmd(exec->cmds);
	if (j < 0)
		j *= -1;
	clean_dir_temp();
	return (j);
}


int execution(t_exec *exec)
{
	int j;
	char **path;
	int 	pid;
	t_cmds	*tmp_cmd;

	tmp_cmd = exec->cmds;

	exec->nb_pipe = nb_pipe(exec->cmds);
	j = 0;
	//================================================================================//
	if (run_here_doc(exec) == 0 && is_builtin(exec->cmds->cmd) && exec->nb_pipe == 1)
		return (exec_sbuiltin(exec));
	//================================================================================//
	
	//================================================================================//
	path = find_path(exec->env);
	exec->previous_fd = -1;
	int i = exec->nb_pipe;
	while (exec->nb_pipe--)
	{
		if (pipe(exec->pipe) == -1)
			return (perror("PIPE ERROR"), 1);
		if (i == 1)
			close(exec->pipe[1]);
		pid = fork();
		if (pid == -1)
			return (perror("FORK ERROR"), 1);
		if (pid == 0)
		{
			signal_exec();
			child_process(exec, path);
		}
		tmp_cmd = exec->cmds;
		exec->cmds = exec->cmds->next;
		ft_free_cmd(tmp_cmd);
		if (exec->previous_fd != -1)
			close(exec->previous_fd);
		exec->previous_fd = exec->pipe[0];
		close(exec->pipe[1]);
	}
	//===================================================================================//
	if (path)
		ft_free(path);
	close(exec->previous_fd);
	j = wait_childs(pid);
	return (clean_dir_temp(), j);
}
