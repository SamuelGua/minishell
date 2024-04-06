/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:18:18 by scely             #+#    #+#             */
/*   Updated: 2024/04/06 15:38:06 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//retour d'erreur minishell ou bash
void ft_exit(t_env **env, char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		exit(0);
	while (str[i])
		i++;
	if (i > 1)
	{
		printf("bash: exit: too many arguments\n");
		return ;
	}
	i = 0;
	while (str[0][i])
	{
		if (ft_isdigit(str[0][i]) == 0)
			exit(2);
		i++;
	}
	exit()
	
}
