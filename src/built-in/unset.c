/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:48:46 by scely             #+#    #+#             */
/*   Updated: 2024/04/10 15:29:29 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Doit on recreer la varaibles _  qui comporte le dernier executable
// Peut-on tout unset
static int	is_head(t_env **env, char *str)
{
	t_env	*tmp;

	if (ft_strncmp((*env)->cle, str, ft_strlen(str)) == 0)
	{
		tmp = (*env);
		*env = (*env)->next;
		(free(tmp->cle), free(tmp->params), free(tmp));
		return (1);
	}
	return (0);
}

static int	is_body(t_env *env, char *str)
{
	t_env	*tmp;

	if (ft_strncmp(env->next->cle, str, ft_strlen(str)) == 0)
	{
		tmp = env->next;
		env->next = tmp->next;
		(free(tmp->cle), free(tmp->params), free(tmp));
		return (1);
	}
	return (0);
}

void	ft_unset(t_export **export, t_env **env, char **str)
{
	t_env	*tmp;
	t_env	*env_temp;
	int		i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		is_head(env, str[i]);
		env_temp = *env;
		while (env_temp->next)
		{
			tmp = env_temp;
			env_temp = env_temp->next;
			if (is_body(tmp, str[i]))
				break ;
		}
		i++;
	}
	ft_free(str);
	free_export(*export);
	*export = init_export(*env);
}
