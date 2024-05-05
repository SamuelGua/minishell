/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/05/04 00:05:15 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	print_message(char *str1, char *str2, char *str3, int fd)
{
	ft_putstr_fd(str1, fd);
	ft_putstr_fd(str2, fd);
	ft_putstr_fd(str3, fd);
}

int main(int ac, char **av, char **envp)
{
	((void)ac, (void)av);
	t_exec				exec;
	struct sigaction	c_signal;
	struct sigaction	slash_signal;

	exec.env = init_env(envp);
 	exec.export = init_export(exec.env);

	sig_c_interactive(&c_signal);
	sig_slash_interactive(&slash_signal);
	exec.error_code = 0;
	while (1)
	{
		sigaction(SIGINT, &c_signal, NULL);
		// sigaction(SIGQUIT, &d_signal, NULL);
		sigaction(SIGQUIT, &slash_signal, NULL);
		exec.prompt = readline("minishell > ");
		if (!exec.prompt)
			return (ft_free_env(exec.env), ft_free_export(exec.export), 2);
		exec.token = init_token(exec.prompt, exec.token);
		if (!exec.token)
		{
			free(exec.prompt);
			continue;
		}
		(add_history(exec.prompt), free(exec.prompt));
		if (is_valid_token(exec.token))
		{
			exec.error_code = 2;
			continue;
		}
		exec.cmds = build_cmd(&exec);
		if (!exec.cmds && errno == ENOMEM)
			return (2);
		else if (!exec.cmds)
		{
			exec.error_code = 0;
			continue ;
		}
		exec.error_code	= execution(&exec);
	}
	return (0);
}

