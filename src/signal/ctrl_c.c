/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:20:54 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 17:57:37 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void interactive_c(int signal_code)
{
	if (signal_code == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_d_exec(int signal_code)
{
	(void)signal_code;
	signal(SIGQUIT, SIG_DFL);
}

void signal_interactive(void)
{
	struct sigaction c_signal;
	struct sigaction slash_signal;

	c_signal.sa_handler = interactive_c;
	c_signal.sa_flags = 0;
	sigemptyset(&c_signal.sa_mask);
	sigaction(SIGINT, &c_signal, NULL);

	slash_signal.sa_handler = SIG_IGN;
	slash_signal.sa_flags = 0;
	sigemptyset(&slash_signal.sa_mask);
	sigaction(SIGQUIT, &slash_signal, NULL);
}

void signal_exec(void)
{
	struct sigaction c_signal;
	struct sigaction slash_signal;

	c_signal.sa_handler = SIG_DFL;
	c_signal.sa_flags = 0;
	sigemptyset(&c_signal.sa_mask);
	sigaction(SIGINT, &c_signal, NULL);

	slash_signal.sa_handler = signal_d_exec;
	slash_signal.sa_flags = 0;
	sigemptyset(&slash_signal.sa_mask);
	sigaction(SIGQUIT, &slash_signal, NULL);
}