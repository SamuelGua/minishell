/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:32 by scely             #+#    #+#             */
/*   Updated: 2024/04/06 14:25:37 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//doit ton le triee par ordre alphabetique

void print_export(t_env *env)
{
	while (env)
	{
		printf("export %s=\"%s\"\n",env->cle, env->params);
		env = env->next;
	}
}

void ft_export(t_env **env, char **str)
{
	t_env *tmp;
	int		i;
	int		j;

	i = 0;
	if (!str)
	{
		print_export(*env);
		return ;
	}
	while (str[i])
	{
		j = 0;
		while(str[i][j] != '=' && str[i][j])
			j++;
		if (!str[i][j])
			break;
		str[i][j] = '\0';
		tmp = ft_lstnew_env(str[i], &str[i][j + 1]);
		if (!tmp)
			return ;
		ft_lstadd_back_env(env, tmp);
		i++;	
	}
	
}