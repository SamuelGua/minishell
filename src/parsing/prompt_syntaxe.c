/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_syntaxe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:30:39 by scely             #+#    #+#             */
/*   Updated: 2024/04/11 18:34:19 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int good_syntaxe(char *prompt)
{
	t_operateur sign;
	int i;

	i = 0;
	while (prompt[i])	
	{
		if (prompt[i] == '\"')
		{
			sign.quoted = 1;
			break;
		}
		if (prompt[i] == '\'')
		{
			sign.quoted = 1;
			break;
		}
		i++;
	}



}