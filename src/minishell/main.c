/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/04/25 09:39:41 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void builtin(char *prompt, t_env **env, t_export **export)
{
		if (ft_strncmp(prompt, "env", 3) == 0)
		{
			char **env_value = ft_split(prompt + 3, ' '); 
			ft_env(*env, env_value);
		}
		else if (ft_strncmp(prompt, "unset", 5) == 0)
		{
			char **unset_value = ft_split(prompt + 5, ' '); 
			ft_unset(export, env, unset_value);
		}
		else if (ft_strncmp(prompt, "echo", 4) == 0)
		{
			char **echo_value = ft_split(prompt + 5, '+');	
			ft_echo(echo_value, *env);
		}
		else if (ft_strncmp(prompt, "export", 6) == 0)
		{
			char **export_value = ft_split(prompt + 6, ' ');	
			ft_export(export, env, export_value);
		}
		else if (ft_strncmp(prompt, "pwd", 3) == 0)	
			ft_pwd();
		else if (ft_strncmp(prompt, "exit", 4) == 0)	
		{
			char **exit_value = ft_split(prompt + 5, ' ');	
			ft_exit(*env, *export, exit_value);
		}
		else if (ft_strncmp(prompt, "cd", 2) == 0)	
		{
			char **cd_value = ft_split(prompt + 2, ' ');	
			ft_cd(*env, cd_value);
		}
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
		prompt = readline("minishell > ");
		if (!prompt)
		{
			ft_free_env(env);
			free_export(export);
			return (2);
		}
		if (ft_split(prompt, ' ') == NULL)
			continue;
		token = init_token(prompt);
		add_history(prompt);
		if (is_valid_token(token))
		{
			free(prompt);
			continue;
		}
		cmd = build_cmd(token, env);
		printf("{%s}\n", cmd->cmd[0]);
		free_token(token);
		//builtin(prompt, &env, &export);
		free(prompt);
	}
	return (0);
}
