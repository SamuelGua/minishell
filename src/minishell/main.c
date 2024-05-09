/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/05/09 18:57:36 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_exit_code = 0;

void	print_message(char *str1, char *str2, char *str3, int fd)
{
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
	ft_putstr_fd(str3, fd);
}

int	main(int ac, char **av, char **envp)
{
	t_exec	exec;

	((void)ac, (void)av);
	exec.env = init_env(envp);
	exec.export = init_export(exec.env);
	exec.error_code = 0;
	while (1)
	{
		g_exit_code = 0;
		signal_interactive();
		exec.prompt = readline("minishell > ");
		if (!exec.prompt)
		{
			ft_putstr_fd("exit\n", 1);
			return (ft_free_env(exec.env), ft_free_export(exec.export),
				exec.error_code);
		}
		if (g_exit_code == 130)
			exec.error_code = g_exit_code;
		exec.token = init_token(exec.prompt, exec.token);
		if (!exec.token)
		{
			free(exec.prompt);
			continue ;
		}
		(add_history(exec.prompt), free(exec.prompt));
		if (is_valid_token(exec.token))
		{
			exec.error_code = 2;
			continue ;
		}
		exec.cmds = build_cmd(&exec);
		if (!exec.cmds && errno == ENOMEM)
			return (2);
		else if (!exec.cmds)
		{
			exec.error_code = 0;
			continue ;
		}
		exec.error_code = execution(&exec);
	}
	rl_clear_history();
	return (0);
}
