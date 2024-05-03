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

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
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

		exec.prompt = readline("\002\033[1;35mminishell > \033[0m\002");
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
			continue;
		exec.cmds = build_cmd(exec.token, exec.env);
		if (!exec.cmds)
			return (0);
		// ft_free_exec(&exec);
		// exit(1);
		execution(&exec);
	}
	return (0);
}
