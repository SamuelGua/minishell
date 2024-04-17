/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:32 by scely             #+#    #+#             */
/*   Updated: 2024/04/17 15:27:40 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// doit ton le triee par ordre alphabetique
// si on export sans la sans la valeur ""

int	print_list(t_export *list)
{
	if (list == NULL)
		return (1);
	if (list->left != NULL)
		print_list(list->left);
	printf("export %s=\"%s\"\n", list->cle, list->params);
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

int	is_valid(char *str)
{
	int	i;

	i = 0;
	// if (ft_isalpha(str[0]) == 1 || str[0] == '_')
	// 	i++;
	// else
	// {
	// 	printf("minishell: export: `%s': not a valid identifier\n", str);
	// 	return (0);
	// }
	while (str[i] != '=' && str[i])
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_export(t_export **export, t_env **env, char **str)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	if (!str && print_list(*export))
		return ;
	while (str[i])
	{
		if (str[i] && is_valid(str[i]) && is_existing(*env, str[i]))
		{
			j = 0;
			while (str[i][j] != '=' && str[i][j])
				j++;
			if (!str[i][j])
				break ;
			str[i][j] = '\0';
			tmp = ft_lstnew_env(str[i], &str[i][j + 1]);
			if (!tmp)
			{
				ft_free(str);
				return ;
			}
			ft_lstadd_back_env(env, tmp);
		}
			i++;
	}
	ft_free(str);
	(free_export(*export), *export = init_export(*env));
}
