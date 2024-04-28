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

int	nb_pipe(t_cmds *cmds)
{
	int i;

	i = 0;
	while (cmds)
	{
		i++;
		cmds = cmds->next;
	}
	return (i -1);
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

void execution(t_exec *exec)
{
	char **path;

	path = find_path(exec->env);
	exec->nb_pipe = nb_pipe(exec->cmds);
	t_cmds *cmds = exec->cmds;
	while (cmds)
	{
		cmds->cmd[0] = valid_cmd(cmds, path);
		printf("cmd = %s\n", cmds->cmd[0]);
		cmds = cmds->next;
	}

}