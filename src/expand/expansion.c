/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 08:59:14 by scely             #+#    #+#             */
/*   Updated: 2024/04/17 11:23:31 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*variables_expand(char *str, t_env *env, int i, int *last_exp, char *new)
{
	int	len;

	len = 0;
	str[i] = '\0';
	i++;
	while (str[i + len] && str[i + len] != 32 && str[i + len] != '$' && str[i + len] != '\'' && str[i + len] != '\'')
		len++;
	while (env && ft_strncmp(&str[i], env->cle, len))
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
			new = ft_strdup(str++);
		else
			new = ft_free_strjoin(new, &str[*last_exp]);
	}
	*last_exp = i + len;
	str[i--] = '$';
	return (new);
}

char	*expansion(char *str, t_env *env)
{
	int		i;
	int		quoted;
	char	*new;
	int		l_expd;

	i = 0;
	l_expd = i;
	new = NULL;
	quoted = NO_QUOTE;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		quoted = is_quoted(quoted, str[i]);
		printf("is quote = %d, %c\n", quoted, str[i]);
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 2] != 32 && quoted != S_QUOTE)
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
