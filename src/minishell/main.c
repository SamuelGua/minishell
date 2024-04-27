/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/04/27 12:31:13 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void builtin(t_cmds *cmd, t_env **env, t_export **export)
{
		if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
			ft_env(*env, cmd->cmd);
		else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
			ft_unset(export, env, cmd->cmd);
		else if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
			ft_echo(cmd->cmd++);
		else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
			ft_export(export, env, cmd->cmd, 0);
		else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)	
			ft_pwd();
		else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)	
			ft_exit(*env, *export, cmd->cmd);
		else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)		
			ft_cd(*env, cmd->cmd);
}

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)ac;
	(void)av;
	t_env 		*env = NULL;
	t_export 	*export = NULL;
	t_token 	*token = NULL;
	t_cmds 		*cmd = NULL;
	env = init_env(envp);
 	export = init_export(env);
	// if (env == NULL)
	// 	return (printf("Erreur malloc\n"), 2);
	while (1)
	{
		prompt = readline("\002\033[1;35mminishell > \033[0m\002");
		if (!prompt)
		{
			ft_free_env(env);
			free_export(export);
			return (2);
		}
		if (ft_split(prompt, ' ') == NULL)
			continue;
		token = init_token(prompt, token);
		add_history(prompt);
		if (is_valid_token(token))
		{
			free(prompt);
			continue;
		}
		cmd = build_cmd(token, env);
		free_token(token);

		if(cmd->type == 1)
			builtin(cmd, &env, &export);
		free(prompt);
	}
	return (0);
}
