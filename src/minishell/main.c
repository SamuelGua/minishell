/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:06:59 by scely             #+#    #+#             */
/*   Updated: 2024/05/15 10:09:39 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

void	print_message(char *str1, char *str2, char *str3, int fd)
{
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
	ft_putstr_fd(str3, fd);
	ft_putstr_fd("\n", fd);
}

int	test(t_exec *exec)
{
	exec->token = init_token(exec->prompt, exec->token);
	if (!exec->token)
	{
		free(exec->prompt);
		return (1);
	}
	add_history(exec->prompt);
	free(exec->prompt);
	if (is_valid_token(exec->token))
	{
		exec->error_code = 2;
		return (1);
	}
	exec->cmds = build_cmd(exec);
	if (!exec->cmds && errno == ENOMEM)
		return (2);
	else if (!exec->cmds)
	{
		exec->error_code = 0;
		return (1);
	}
	return (0);
}

void	init_value(t_exec *exec, char **av, char **envp)
{
	(void)av;
	exec->env = init_env(envp);
	exec->export = init_export(exec->env);
	exec->error_code = 0;
}

int	main(int ac, char **av, char **envp)
{
	t_exec	exec;

	init_value(&exec, av, envp);
	while (1)
	{
		g_exit_code = 0;
		signal_interactive();
		exec.prompt = readline("minishell > ");
		if (g_exit_code == 130)
			exec.error_code = g_exit_code;
		if (!exec.prompt)
		{
			ft_putstr_fd("exit\n", 1);
			rl_clear_history();
			(ft_free_env(exec.env), ft_free_export(exec.export));
			return (exec.error_code);
		}
		ac = test(&exec);
		if (ac == 1)
			continue ;
		else if (ac == 2)
			return (rl_clear_history(), 2);
		exec.error_code = execution(&exec);
	}
	return (0);
}
