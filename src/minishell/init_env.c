/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:57:54 by scely             #+#    #+#             */
/*   Updated: 2024/04/06 14:12:46 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (*lst)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*lst = new;
}
t_env	*ft_lstnew_env(char *str1, char *str2)
{
	t_env	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->cle = ft_strdup(str1);
	if (!new->cle)
		return(free(new), NULL);
	new->params = ft_strdup(str2);
	if (!new->params)
		return (free(new->cle), free(new), NULL);
	new->next = NULL;
	return (new);
}

void	ft_free_env(t_env *env)
{
	t_env *tmp ;

	while (!env)
	{
		tmp = env->next;
		free(env->next);
		free(env->params);
		free(env);
		env = tmp;
	}
}

t_env	*init_env(char **envp)
{
	t_env *env;
	t_env *tmp;
	int		i;
	int		j;

	i = 0;
	if (envp == NULL)
	{
		printf("NO environement\n");
		return (NULL);
	}
	while (envp[i])
	{
		j = 0;
		while(envp[i][j] != '=' && envp[i])
			j++;
		envp[i][j] = '\0';
		tmp = ft_lstnew_env(envp[i],&envp[i][j+1]);
		if (!tmp)
			return (ft_free_env(env), NULL);
		ft_lstadd_back_env(&env, tmp);
		i++;
	}
	return (env);
}