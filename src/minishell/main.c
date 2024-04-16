/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/04/12 17:52:19 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)ac;
	(void)av;
	t_env 		*env = NULL;
	t_export 	*export = NULL;
	t_token 	*token = NULL;
	env = init_env(envp);
 	export = init_export(env);
	// if (env == NULL)
	// 	return (printf("Erreur malloc\n"), 2);
	while (1)
	{
		prompt = readline("\033[1;32mminishell > \033[0m");
		if (!prompt)
			return (2);
		token = init_token(prompt);
		print_token(token);
		free_token(token);
		add_history(prompt);

		if (ft_strncmp(prompt, "env", 3) == 0)
		{
			char **env_value = ft_split(prompt + 3, ' '); 
			ft_env(env, env_value);
		}
		else if (ft_strncmp(prompt, "unset", 5) == 0)
		{
			char **unset_value = ft_split(prompt + 5, ' '); 
			ft_unset(&export, &env, unset_value);
		}
		else if (ft_strncmp(prompt, "echo", 4) == 0)
		{
			char **echo_value = ft_split(prompt + 4, ' ');	
			ft_echo(echo_value, env);
		}
		else if (ft_strncmp(prompt, "export", 6) == 0)
		{
			char **export_value = ft_split(prompt + 6, ' ');	
			ft_export(&export, &env, export_value);
		}
		else if (ft_strncmp(prompt, "pwd", 3) == 0)	
			ft_pwd();
		else if (ft_strncmp(prompt, "exit", 4) == 0)	
		{
			char **exit_value = ft_split(prompt + 5, ' ');	
			ft_exit(env, export, exit_value);
		}
		else if (ft_strncmp(prompt, "cd", 2) == 0)	
		{
			char **cd_value = ft_split(prompt + 2, ' ');	
			ft_cd(env, cd_value);
		}
	}
	return (0);    
}
