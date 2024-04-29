/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/04/29 21:31:00 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void builtin(t_cmds *cmd, t_env **env, t_export **export)
{
		if (ft_strcmp(cmd->cmd[0], "env") == 0)
			ft_env(*env, cmd->cmd);
		else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
			ft_unset(export, env, cmd->cmd);
		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
			ft_echo(cmd->cmd++);
		else if (ft_strcmp(cmd->cmd[0], "export") == 0)
			ft_export(export, env, cmd->cmd, 0);
		else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)	
			ft_pwd();
		else if (ft_strcmp(cmd->cmd[0], "exit") == 0)	
			ft_exit(*env, *export, cmd->cmd);
		else if (ft_strcmp(cmd->cmd[0], "cd") == 0)		
			ft_cd(*env, cmd->cmd);
}

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)ac;
	(void)av;
	t_exec		exec;
	t_token 	*token = NULL;

	exec.env = init_env(envp);
 	exec.export = init_export(exec.env);
	// if (env == NULL)
	// 	return (printf("Erreur malloc\n"), 2);
	while (1)
	{
		prompt = readline("\002\033[1;35mminishell > \033[0m\002");
		if (!prompt)
		{
			ft_free_env(exec.env);
			free_export(exec.export);
			return (2);
		}
		if (ft_split(prompt, ' ') == NULL)
			continue;
		token = init_token(prompt, token);
		add_history(prompt);
		free(prompt);
		if (is_valid_token(token))
			continue;
		exec.cmds = build_cmd(token, exec.env);
		if(exec.cmds->type == 1)
		{
			builtin(exec.cmds, &exec.env, &exec.export);
			continue;
		}
		execution(&exec);
	}
	return (0);
}
