/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:51:46 by scely             #+#    #+#             */
/*   Updated: 2024/05/10 13:27:40 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_exec *exec, char **path)
{
	int	i;

	i = check_errors(exec, path);
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
	exit(127);
}

int	exec_sbuiltin(t_exec *exec)
{
	int	j;
	int	fd_orgin[2];

	fd_orgin[0] = dup(STDIN_FILENO);
	fd_orgin[1] = dup(STDOUT_FILENO);
	j = redirection(exec);
	if (j >= 0 && exec->cmds->cmd[0])
		j = builtin(exec, fd_orgin, 1);
	dup2(fd_orgin[1], STDOUT_FILENO);
	dup2(fd_orgin[0], STDIN_FILENO);
	close(fd_orgin[1]);
	close(fd_orgin[0]);
	ft_free_cmd(exec->cmds);
	if (j < 0)
		j *= -1;
	clean_dir_temp();
	return (j);
}

void error_pf(char **path, t_exec *exec, t_cmds * tmp_cmd, char *str)
{
	perror(str);
	if (path)
		ft_free(path);
	if (exec->previous_fd != -1)
		close(exec->previous_fd);
	if (close(exec->pipe[0]) != -1)
		close(exec->pipe[0]);
	if (close(exec->pipe[1]) != -1)
		close(exec->pipe[1]);
	clean_dir_temp();
	while (exec->cmds)
	{
		tmp_cmd = exec->cmds;
		exec->cmds = exec->cmds->next;
		ft_free_cmd(tmp_cmd);
	}
}


int	execution(t_exec *exec)
{
	char	**path;
	int		pid;
	t_cmds	*tmp_cmd;
	int		code_here;
	int		i;

	tmp_cmd = exec->cmds;
	exec->nb_pipe = nb_pipe(exec->cmds);
	code_here = run_here_doc(exec);
	if (code_here == 0 && is_builtin(exec->cmds->cmd) && exec->nb_pipe == 1)
		return (exec_sbuiltin(exec));
	if (code_here == 130)
	{
		clean_dir_temp();
		while (exec->cmds)
		{
			tmp_cmd = exec->cmds;
			exec->cmds = exec->cmds->next;
			ft_free_cmd(tmp_cmd);
		}
		return (130);
	}
	path = find_path(exec->env);
	exec->previous_fd = -1;
	i = exec->nb_pipe;
	signal(SIGINT, SIG_IGN);
	exec->pipe[0] = -1;
	exec->pipe[1] = -1;
	while (exec->nb_pipe--)
	{
		if (pipe(exec->pipe) == -1)
			return (error_pf(path, exec, tmp_cmd, "PIPE ERROR"), 1);
		if (i == 1)
			close(exec->pipe[1]);
		pid = fork();
		if (pid == -1)
			return (error_pf(path, exec, tmp_cmd, "FORK ERROR"), 1);
		if (pid == 0)
			(signal_exec(), child_process(exec, path));
		tmp_cmd = exec->cmds;
		exec->cmds = exec->cmds->next;
		ft_free_cmd(tmp_cmd);
		if (exec->previous_fd != -1)
			close(exec->previous_fd);
		exec->previous_fd = exec->pipe[0];
		close(exec->pipe[1]);
	}
	if (path)
		ft_free(path);
	close(exec->previous_fd);
	i = wait_childs(pid);
	if (i == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (i == 130)
		printf("\n");
	return (clean_dir_temp(), i);
}
