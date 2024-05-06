/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:45:36 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 10:56:48 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env, char **str)
{
	if (str[1])
	{
		
		// printf("No arguments required\n");
		return (0);
	}
	while (env)
	{
		ft_putstr_fd(env->cle, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env->params, 1);
		ft_putstr_fd("\n", 1);
		// printf("%s=%s\n", env->cle, env->params);
		env = env->next;
	}
	return (0);
}
