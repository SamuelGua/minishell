/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:45:36 by scely             #+#    #+#             */
/*   Updated: 2024/05/04 04:35:35 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env, char **str)
{
	if (str[1])
	{
		printf("No arguments required\n");
		return (0);
	}
	while (env)
	{
		printf("%s=%s\n", env->cle, env->params);
		env = env->next;
	}
	return (0);
}
