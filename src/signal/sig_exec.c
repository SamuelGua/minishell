/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:31:25 by scely             #+#    #+#             */
/*   Updated: 2024/05/10 13:35:01 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_slash_exec(int signal_code)
{
	(void)signal_code;
	signal(SIGQUIT, SIG_DFL);
}

void	signal_exec(void)
{
	struct sigaction	c_signal;
	struct sigaction	slash_signal;

	c_signal.sa_handler = SIG_DFL;
	c_signal.sa_flags = 0;
	sigemptyset(&c_signal.sa_mask);
	sigaction(SIGINT, &c_signal, NULL);
	slash_signal.sa_handler = signal_slash_exec;
	slash_signal.sa_flags = 0;
	sigemptyset(&slash_signal.sa_mask);
	sigaction(SIGQUIT, &slash_signal, NULL);
}
