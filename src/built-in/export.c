/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:32 by scely             #+#    #+#             */
/*   Updated: 2024/05/16 23:16:03 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_list(t_export *list)
{
	int	i;

	i = 0;
	if (list == NULL)
		return (1);
	if (list->left != NULL)
		print_list(list->left);
	printf("export %s=\"%s\"\n", list->cle, list->params);
	if (i == -1)
		perror("export :");
	if (list->right != NULL)
		print_list(list->right);
	return (1);
}

static int	is_existing(t_env *env, char *str)
{
	int	j;

	j = 0;
	while (str[j] != '=' && str[j])
		j++;
	if (!str[j])
		return (1);
	str[j] = '\0';
	while (env && ft_strcmp(env->cle, str) != 0)
		env = env->next;
	str[j] = '=';
	if (!env)
		return (1);
	free(env->params);
	env->params = ft_strdup(&str[++j]);
	return (0);
}

int	is_valid(char *str, int *c)
{
	int	i;

	i = 0;
	if (str[i] != '_' && ft_isalpha(str[i]) == 0)
	{
		(ft_putstr_fd("minishell: export: ", 2), *c = 1);
		(ft_putstr_fd(str, 2), ft_putstr_fd(": not a valid identifier\n", 2));
		return (0);
	}
	i++;
	while (str[i] != '=' && str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			(ft_putstr_fd("minishell: export: ", 2), *c = 1);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
			return (0);
		}
		i++;
	}
	if (!str[i] || str[i + 1] == '\0')
		return (1);
	return (1);
}

int	ft_export(t_export **export, t_env **env, char **str, int i)
{
	t_env	*tmp;
	int		j;
	int		c;

	c = 0;
	if (!str[1] && print_list(*export))
		return (0);
	while (str[++i])
	{
		if (is_valid(str[i], &c) == 0)
			continue ;
		else if (is_existing(*env, str[i]))
		{
			j = 0;
			while (str[i][j] && str[i][j] != '=')
				j++;
			if (!str[i][j])
				continue ;
			str[i][j] = '\0';
			tmp = ft_lstnew_env(str[i], &str[i][j + 1]);
			ft_lstadd_back_env(env, tmp);
			(ft_free_export(*export), *export = init_export(*env));
		}
	}
	return (c);
}
