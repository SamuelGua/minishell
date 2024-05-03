/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:51:46 by scely             #+#    #+#             */
/*   Updated: 2024/05/04 01:09:00 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	print_message(char *str1, char *str2, char *str3, int fd)
{
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
	ft_putstr_fd(str3, fd);
}

int	valid_cmd(t_exec *exec, char **path)
{
	char *new;
	int i;

	i = 0;
	struct stat fileinfo;

	if (exec->cmds->cmd[0][0] == '\0')
		return(1);
	if (exec->cmds->cmd[0][0] == '.' && exec->cmds->cmd[0][1] == '/')
	{
		if (stat(exec->cmds->cmd[0], &fileinfo) == -1)
        	return (perror("stat"), 1);
			// return (1);

		if (S_ISDIR(fileinfo.st_mode))
		{
			print_message("minishell: ", exec->cmds->cmd[0], ": Is a directory\n", 2);
			return (1);
			// return (1);
		}
    	else if (access(exec->cmds->cmd[0], X_OK))
		{
			perror("");
			return (1);
			// return (1);
		}
	}
	new = ft_strdup(exec->cmds->cmd[0]);
	if (!new)
		return (printf("Error malloc\n"), 2);
			// return (1);

	while (access(new, X_OK) && path && path[i])
	{
		free(new);
		new = ft_strjoin(path[i], exec->cmds->cmd[0]);
		if (!new)
			return (printf("Error malloc\n"), 2);
			// return (1);

		i++;
	}
	if (access(new, X_OK))
	{
		print_message("minishell: ", exec->cmds->cmd[0], " : command not found\n", 2);
		return (free(new), 127);
			// return (1);

	}
	free(exec->cmds->cmd[0]);
	exec->cmds->cmd[0] = new;
	return (0);
	// change variable
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
	if (exec->cmds->cmd[0] && is_builtin(exec->cmds->cmd))
	{
		builtin(exec);
		if (path)
			ft_free(path);
		close(exec->pipe[1]);
		ft_free_exec(exec);
		exit(0);
	}
	if (exec->cmds->cmd[0])
		if (valid_cmd(exec, path))
		{
			ft_free(path);
			close(exec->pipe[1]);
			ft_free_exec(exec);
			exit (127);
		}
	if (path)
		ft_free(path);
	if (!exec->cmds->cmd[0])
	{
		ft_free_exec(exec);
		close(exec->pipe[1]);
		exit(127);
	}
	exec->exec_envp = build_envp(exec->env);
	execve(exec->cmds->cmd[0], exec->cmds->cmd, exec->exec_envp);
	perror("");
	ft_free_exec(exec);
	close(exec->pipe[1]);
	exit(1);
}


void execution(t_exec *exec)
{
	char **path;
	int 	pid;
	t_cmds	*tmp_cmd;

	tmp_cmd = exec->cmds;
	struct sigaction signal;
	signal.sa_handler = c_quite_exec;
	signal.sa_flags = 0;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);

	struct sigaction slash_signal;
	slash_signal.sa_handler = slash_exec;
	slash_signal.sa_flags = 0;
	sigemptyset(&slash_signal.sa_mask);
	sigaction(SIGQUIT, &slash_signal, NULL);

	path = find_path(exec->env);
	exec->nb_pipe = nb_pipe(exec->cmds);
	run_here_doc(exec);
	if (exec->cmds->cmd[0] && is_builtin(exec->cmds->cmd) && exec->nb_pipe == 1)
	{
		int dup_in = dup(STDIN_FILENO);
		int dup_out = dup(STDOUT_FILENO);;
		redirection(exec);
		builtin(exec);
		dup2(dup_out, STDOUT_FILENO);
		dup2(dup_in, STDIN_FILENO);
		close(dup_out);
		close(dup_in);
		ft_free_cmd(exec->cmds);
		return ;
	}
	//================================================================================//
	exec->previous_fd = -1;
	int i = exec->nb_pipe;
	while (exec->nb_pipe--)
	{
		if (pipe(exec->pipe) == -1)
		{
			perror("PIPE ERROR");
			return ;
		}
		if (i == 1)
			close(exec->pipe[1]);
		pid = fork();
		if (pid == -1)
		{
			perror("FORK ERROR");
			return ;
		}
		if (pid == 0)
			child_process(exec, path);
		tmp_cmd = exec->cmds;
		exec->cmds = exec->cmds->next;
		ft_free_cmd(tmp_cmd);
		if (exec->previous_fd != -1)
			close(exec->previous_fd);
		exec->previous_fd = exec->pipe[0];
		close(exec->pipe[1]);
	}
	//===================================================================================//
	ft_free(path);
	close(exec->previous_fd);
	wait_childs(pid);
	clean_dir_temp();
}
