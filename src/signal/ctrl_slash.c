/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_slash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:38:22 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 17:39:13 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	slash_exec(int signal)
{
	if (signal == SIGQUIT)
		return ;
	return ;
}

void sig_slash_interactive(struct sigaction *sig_struct)
{
	sig_struct->sa_handler = SIG_IGN;
	sig_struct->sa_flags = 0;
	sigemptyset(&sig_struct->sa_mask);
}

void sig_slash_exec(struct sigaction *sig_struct)
{
	sig_struct->sa_handler = SIG_DFL;
	sig_struct->sa_flags = 0;
	sigemptyset(&sig_struct->sa_mask);
}