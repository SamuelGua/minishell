/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:56:41 by scely             #+#    #+#             */
/*   Updated: 2024/05/04 04:09:03 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//getenv
// modifier les environements
typedef struct s_cdutils
{
	t_env *pwd;
	t_env *oldpwd;
	char *previous_pwd;
}	t_cdutils;

t_env *ft_getenv(t_env *env, char *str)
{
	while (env)
	{
		if (!strcmp(env->cle, str))
			break;
		env = env->next;
	}
	return (env);
}

void update_cd(t_cdutils *pwd)
{
	if (pwd->oldpwd)
	{
		free(pwd->oldpwd->params);
		pwd->oldpwd->params = ft_strdup(pwd->previous_pwd);
	}
	if (pwd->pwd)
	{
		free(pwd->pwd->params);
		pwd->pwd->params = getcwd(NULL, 0);
	}
	if (pwd->previous_pwd)
		free(pwd->previous_pwd);
}

int	cd_home(t_env *env, t_cdutils *pwd)
{
	char	*error;

	while (env && ft_strcmp(env->cle, "HOME") != 0)
		env = env->next;
	if (!env)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(env->params))
	{
		error = ft_strjoin("minishell: cd: ", env->params);
		perror(error);
		free(error);
		return (1);
	}
	update_cd(pwd);
	return (0);
}

int ft_cd(t_env *env, char **str)
{
	int		i;
	char	*error;
	t_cdutils	pwd;

	pwd.oldpwd = ft_getenv(env, "OLDPWD");
	pwd.pwd = ft_getenv(env, "PWD");
	pwd.previous_pwd = getcwd(NULL, 0);
	i = 1;
	if (!str[i])
		return (cd_home(env, &pwd));
	while (str[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		return (free(pwd.previous_pwd), 1 );
	}
	if (chdir(str[1]))
	{
		error = ft_strjoin("bash: cd: ", str[1]);
		(perror(error), free(error), free(pwd.previous_pwd));
		return (1);
	}
	update_cd(&pwd);
	return (0);
}
