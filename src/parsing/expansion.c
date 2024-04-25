/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:12:48 by scely             #+#    #+#             */
/*   Updated: 2024/04/25 18:48:06 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_expand
{
	int		i;
	char	*new;
	int		l_exp;
	int		quoted;

}	t_exutils;

void	add_expand(char *str, t_env *env, t_exutils *ex)
{
	int	len;

	len = 0;
	while (str[ex->i + len + 1] && check_whitespace(str[ex->i + len + 1]) != 1
		&& str[ex->i + len + 1] != '\'' && str[ex->i + len + 1] != '/'
		&& str[ex->i + len + 1] != '\"' && str[ex->i + len + 1] != '$')
		len++;
	str[ex->i] = '\0';
	printf("len %i\n", len);
	ex->new = ft_free_strjoin(ex->new, &str[ex->l_exp]);
	while (env && (ft_strncmp(&str[ex->i + 1], env->cle, len) != 0
			|| len != (int)ft_strlen(env->cle)))
		env = env->next;
	if (env)
		ex->new = ft_free_strjoin(ex->new, env->params);
	str[ex->i] = '$';
	ex->l_exp = ex->i + len + 1;
	ex->i = ex->l_exp;
}

void	dollar_dollar(char *str, t_env *env, t_exutils *ex)
{
	char	*sys;

	sys = "SYSTEMD_EXEC_PID";
	str[ex->i] = '\0';
	ex->new = ft_free_strjoin(ex->new, &str[ex->l_exp]);
	while (env && (ft_strncmp(sys, env->cle, 16) != 0
			|| 16 != (int)ft_strlen(env->cle)))
		env = env->next;
	if (env)
		ex->new = ft_free_strjoin(ex->new, env->params);
	str[ex->i] = '$';
	ex->l_exp = ex->i + 1 + 1;
	ex->i = ex->l_exp;
}

void	expansion_two(t_exutils *ex, char *str, t_env *env)
{
	while (str[ex->i] && check_whitespace(str[ex->i]))
		ex->i++;
	ex->l_exp = ex->i;
	while (str[ex->i])
	{
		ex->quoted = is_quoted(ex->quoted, str[ex->i]);
		if (str[ex->i] == '$' && str[ex->i + 1] == '$' && ex->quoted != S_QUOTE)
			dollar_dollar(str, env, ex);
		else if (str[ex->i] == '$' && check_whitespace(str[ex->i + 1]) != 1
			&& str[ex->i + 1] != '\0' && ex->quoted != S_QUOTE)
			add_expand(str, env, ex);
		else
			ex->i++;
	}
}

char	*expansion(char *str, t_env *env)
{
	t_exutils	ex;
	char		c;

	ex.i = 0;
	ex.new = ft_calloc(1, 1);
	ex.quoted = NO_QUOTE;
	while (str[ex.i] && str[ex.i] != '$'
		&& check_whitespace(str[ex.i + 1]) == 0 && ex.quoted != S_QUOTE)
	{
		ex.quoted = is_quoted(ex.quoted, str[ex.i]);
		ex.i++;
	}
	if (!str[ex.i])
		return (str);
	if (str[ex.i] || str[ex.i] == '$')
	{
		c = str[ex.i];
		str[ex.i] = '\0';
		ex.new = ft_strdup(str);
		str[ex.i] = c;
	}
	expansion_two(&ex, str, env);
	ex.new = ft_free_strjoin(ex.new, &str[ex.l_exp]);
	return (ex.new);
}
