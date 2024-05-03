/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_slash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:38:22 by scely             #+#    #+#             */
/*   Updated: 2024/05/03 15:39:20 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	slash_dump(int signal)
{
	int *i = NULL;
	if (signal == SIGQUIT)
		printf("%d", *i);
	return ;
}

void	slash_exec(int signal)
{
	if (signal == SIGQUIT)
		return ;
	return ;
}

void sig_slash_interactive(struct sigaction *sig_struct)
{
	sig_struct->sa_handler = slash_dump;
	sig_struct->sa_flags = 0;
	sigemptyset(&sig_struct->sa_mask);
}