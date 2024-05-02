/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/05/02 18:30:33 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void builtin(t_exec *exec)
{
		if (ft_strcmp(exec->cmds->cmd[0], "env") == 0)
			ft_env(exec->env, exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "unset") == 0)
			ft_unset(&exec->export, &exec->env, exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "echo") == 0)
			ft_echo(exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "export") == 0)
			ft_export(&exec->export, &exec->env, exec->cmds->cmd, 0);
		else if (ft_strcmp(exec->cmds->cmd[0], "pwd") == 0)	
			ft_pwd();
		else if (ft_strcmp(exec->cmds->cmd[0], "exit") == 0)	
			ft_exit(exec->env, exec->export, exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "cd") == 0)		
			ft_cd(exec->env, exec->cmds->cmd);
}


void print_b(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
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
	struct sigaction signal;
	signal.sa_handler = print_b;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	
	//sigaction(2);
	while (1)
	{
		prompt = readline("\002\033[1;35mminishell > \033[0m\002");
		// if (!prompt)
		// {
		// 	ft_free_env(exec.env);
		// 	free_export(exec.export);
		// 	return (2);
		// }
		char **lol = ft_split(prompt, ' ');
		if (lol == NULL)
			continue ;
		else
			ft_free(lol);
		token = init_token(prompt, token);
		add_history(prompt);
		free(prompt);
		if (is_valid_token(token))
			continue;

		exec.cmds = build_cmd(token, exec.env);
		//print_lst_cmd(exec.cmds);

		execution(&exec);
	/* 	ft_free_exec(&exec);
		exit(1); */
	}
	return (0);
}
