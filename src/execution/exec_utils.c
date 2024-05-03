/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 22:13:55 by scely             #+#    #+#             */
/*   Updated: 2024/05/03 22:14:54 by scely            ###   ########.fr       */
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
	while (path && path[i])
	{
		path[i] = ft_free_strjoin(path[i], "/");
		i++;
	}
	return (path);
}