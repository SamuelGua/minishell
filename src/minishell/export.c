/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:32 by scely             #+#    #+#             */
/*   Updated: 2024/04/06 15:14:57 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//doit ton le triee par ordre alphabetique

static int is_existing(t_env *env, char *str)
{
	int j;

	j = 0;
	while (str[j] != '=' && str[j])
		j++;
	j++;
	if (!str[j])
		return (1);
	printf("str %s str[i] %s\n", str, &str[j]);
	while (env && ft_strncmp(env->cle, str, j - 1) != 0)
		env = env->next;
	if (!env)
		return (1);
	printf("ok\n");
	printf("PARAMS %s\n",env->params);
	free(env->params);
	env->params = ft_strdup(&str[j]);
	return (0);
}

static void print_export(t_env *env)
{
	while (env)
	{
		printf("export %s=\"%s\"\n",env->cle, env->params);
		env = env->next;
	}
}

void ft_export(t_env **env, char **str)
{
	t_env	*tmp;
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
		if (is_existing(*env, str[i]))
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
		}
		i++;
	}
}
