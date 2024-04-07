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

static void sort_env(t_env **export)
{
	if (!export || !(*export)->next)
		return;
	t_env *swap;
	t_env *tmp;
	int	i = 100;
	int k; t_env *head;

	head = (*export);
	while (i--)
	{
		tmp = head;
		k = 0;
		while (tmp->next)
		{
			if (ft_strncmp(tmp->cle, tmp->next->cle, 100) > 0)
			{
				swap = tmp->next;
				tmp->next = swap->next;
				swap->next = tmp;
				if (k == 0)
				{
					head = tmp;
					k++;
				}
			}
			tmp = tmp->next;
		}
	}
	*export = head;
}

static int is_existing(t_env *env, char *str)
{
	int j;

	j = 0;
	while (str[j] != '=' && str[j])
		j++;
	j++;
	if (!str[j])
		return (1);
	while (env && ft_strncmp(env->cle, str, j - 1) != 0)
		env = env->next;
	if (!env)
		return (1);
	free(env->params);
	env->params = ft_strdup(&str[j]);
	return (0);
}

static int print_export(t_env *env)
{
	t_env *export;
	t_env *tmp;

	export = NULL;
	while(env)
	{
		tmp = ft_lstnew_env(env->cle, env->params);
		if (!tmp)
		{
			printf("Error malloc\n");
			return (ft_free_env(export), 1);
		}
		ft_lstadd_back_env(&export, tmp);
		env = env->next;
	}
	sort_env(&export);
	tmp = export;
	while (export)
	{
		printf("export %s=\"%s\"\n",export->cle, export->params);
		export = export->next;
	}
	ft_free_env(tmp);
	return (1);
}

void ft_export(t_env **env, char **str)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	if (!str && print_export(*env))
		return ;
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
