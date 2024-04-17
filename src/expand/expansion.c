/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:59:14 by scely             #+#    #+#             */
/*   Updated: 2024/04/17 17:06:05 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variables_expand(char *str, t_env *env, int i, int *last_exp, char *new)
{
	int	len;

	len = 0;
	str[i] = '\0';
	i++;
	while (str[i + len] && str[i + len] != 32 && str[i + len] != '$' && str[i + len] != '\'' && str[i + len] != '\"')
		len++;
	while (env && ft_strncmp(&str[i], env->cle, (int)ft_strlen(env->cle)))
		env = env->next;
	if (env)
	{
		if (!new)
		{
			new = ft_strdup(str);
			new = ft_free_strjoin(new, env->params);
		}
		else
		{
			new = ft_free_strjoin(new, &str[*last_exp]);
			new = ft_free_strjoin(new, env->params);
		}
	}
	else
	{
		if (!new)
			new = ft_strdup(str);
		else
			new = ft_free_strjoin(new, &str[*last_exp]);
	}
	*last_exp = i + len;
	str[i] = '$';
	return (new);
}

char	*dollar_dollar(char *str, t_env *env, int i, int *last_exp, char *new)
{
	char *dollar2;

	dollar2 = "SYSTEMD_EXEC_PID";
	str[i] = '\0';
	i++;
	while (env && ft_strncmp(dollar2, env->cle, (int)ft_strlen(env->cle)))
		env = env->next;
	if (env)
	{
		if (!new)
		{
			new = ft_strdup(str);
			new = ft_free_strjoin(new, env->params);
		}
		else
		{
			new = ft_free_strjoin(new, &str[*last_exp]);
			new = ft_free_strjoin(new, env->params);
		}
	}
	else
	{
		if (!new)
			new = ft_strdup(str);
		else
			new = ft_free_strjoin(new, &str[*last_exp]);
	}
	str[i] = '$';
	return (new);
}
char	*expansion(char *str, t_env *env)
{
	int		i;
	int		quoted;
	char	*new;
	int		l_expd;

	i = 0;
	l_expd = 0;
	new = NULL;
	quoted = NO_QUOTE;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		quoted = is_quoted(quoted, str[i]);
		if (str[i] == '$' && str[i + 1] == '$')
		{
			new =  dollar_dollar(str, env, i, &l_expd, new);
			i += 2;
			l_expd += 2;
		}
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != 32 && quoted != S_QUOTE)
		{
			new = variables_expand(str, env, i, &l_expd, new);
			i = l_expd;
		}
		else
			i++;
	}
	if (!new)
		return (str);
	else
		new = ft_free_strjoin(new, &str[l_expd]);
	return (new);
}
