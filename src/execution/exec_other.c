/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 15:38:39 by scely             #+#    #+#             */
/*   Updated: 2024/05/15 12:15:04 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_utils_one(int *code_here, t_exec *exec, t_cmds *tmp_cmd, char ***path)
{
	if (*code_here == 130)
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
	exec->nb_pipe = nb_pipe(exec->cmds);
	*path = find_path(exec->env);
	exec->previous_fd = -1;
	signal(SIGINT, SIG_IGN);
	exec->pipe[0] = -1;
	exec->pipe[1] = -1;
	return (0);
}

void	exec_utils_two(int pid, t_exec *exec, char ***path, t_cmds *tmp_cmd)
{
	if (pid == 0)
		(signal_exec(), child_process(exec, *path));
	tmp_cmd = exec->cmds;
	exec->cmds = exec->cmds->next;
	ft_free_cmd(tmp_cmd);
	if (exec->previous_fd != -1)
		close(exec->previous_fd);
	exec->previous_fd = exec->pipe[0];
	close(exec->pipe[1]);
}

int	exec_utils_three(int pid, char ***path, t_exec *exec)
{
	int	i;

	i = 0;
	if (*path)
		ft_free(*path);
	close(exec->previous_fd);
	i = wait_childs(pid);
	if (i == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (i == 130)
		printf("\n");
	clean_dir_temp();
	return (i);
}
