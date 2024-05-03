/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:20:54 by scely             #+#    #+#             */
/*   Updated: 2024/05/03 15:37:23 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void c_new_prompt(int signal)
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
void	c_quite_exec(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	return ;
}

void sig_c_interactive(struct sigaction *sig_struct)
{
	
	sig_struct->sa_handler = c_new_prompt;
	sig_struct->sa_flags = 0;
	sigemptyset(&sig_struct->sa_mask);
}