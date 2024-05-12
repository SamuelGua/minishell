/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:51:46 by scely             #+#    #+#             */
/*   Updated: 2024/05/12 16:56:07 by scely            ###   ########.fr       */
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
		rl_clear_history();
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
	rl_clear_history();
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

void	error_pf(char **path, t_exec *exec, t_cmds *tmp_cmd, char *str)
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

// pour compter le nombre de pipe que j'ai dans ma commande jai choisi
// de le stocker dans la variable code_here
int	execution(t_exec *exec)
{
	char	**path;
	int		pid;
	t_cmds	*tmp_cmd;
	int		code_here;

	tmp_cmd = exec->cmds;
	code_here = run_here_doc(exec);
	if (code_here == 0 && is_builtin(exec->cmds->cmd)
		&& nb_pipe(exec->cmds) == 1)
		return (exec_sbuiltin(exec));
	if (exec_utils_one(&code_here, exec, tmp_cmd, &path) == 130)
		return (130);
	code_here = exec->nb_pipe;
	while (exec->nb_pipe--)
	{
		if (pipe(exec->pipe) == -1)
			return (error_pf(path, exec, tmp_cmd, "PIPE ERROR"), 1);
		if (code_here == 1)
			close(exec->pipe[1]);
		pid = fork();
		if (pid == -1)
			return (error_pf(path, exec, tmp_cmd, "FORK ERROR"), 1);
		exec_utils_two(pid, exec, &path, tmp_cmd);
	}
	return (exec_utils_three(pid, &path, exec));
}
