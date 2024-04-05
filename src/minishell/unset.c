/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:48:46 by scely             #+#    #+#             */
/*   Updated: 2024/04/05 16:53:59 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env *env, char *str)
{
	t_env	*tmp;
	int		str_len;

	if (!str)
		return ;
	str_len = ft_strlen(str);
	while (env && ft_strncmp(env->cle, str, str_len) != 0)
	{
		tmp = env;
		env = env->next;
	}
	tmp->next = env->next;
	free(env->cle);
	free(env->params);
	free(env);
}