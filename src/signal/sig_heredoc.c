/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:32:40 by scely             #+#    #+#             */
/*   Updated: 2024/05/10 13:32:56 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_c_heredoc(int signal_code)
{
	g_exit_code = 5;
	(void)signal_code;
	close(0);
}

void	signal_heredoc(void)
{
	struct sigaction	c_signal;

	c_signal.sa_handler = signal_c_heredoc;
	c_signal.sa_flags = 0;
	sigemptyset(&c_signal.sa_mask);
	sigaction(SIGINT, &c_signal, NULL);
}
