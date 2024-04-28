/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:56:41 by scely             #+#    #+#             */
/*   Updated: 2024/04/26 09:17:24 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//getenv
// modifier les environements
int	cd_home(t_env *env)
{
	char	*error;

	while (env && ft_strcmp(env->cle, "HOME") != 0)
		env = env->next;
	if (!env)
		return (printf("bash: cd: HOME not set\n"));
	if (chdir(env->params))
	{
		error = ft_strjoin("bash: cd: ", env->params);
		perror(error);
		free(error);
	}
	return (0);
}

void	ft_cd(t_env *env, char **str)
{
	int		i;
	char	*error;

	i = 1;
	if (!str[i])
	{
		cd_home(env);
		return ;
	}
	while (str[i])
		i++;
	if (i > 2)
	{
		printf("bash: cd: too many arguments\n");
		return ;
	}
	if (chdir(str[1]))
	{
		error = ft_strjoin("bash: cd: ", str[1]);
		perror(error);
		free(error);
	}
	ft_free(str);
}
