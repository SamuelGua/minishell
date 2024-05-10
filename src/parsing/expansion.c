/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:12:48 by scely             #+#    #+#             */
/*   Updated: 2024/05/10 09:20:21 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_expand(char *str, t_env *env, t_exutils *ex)
{
	int	len;

	len = 0;
	while (str[ex->i + len + 1] && check_whitespace(str[ex->i + len + 1]) != 1
		&& str[ex->i + len + 1] != '\'' && str[ex->i + len + 1] != '/'
		&& str[ex->i + len + 1] != '\"' && str[ex->i + len + 1] != '$')
		len++;
	str[ex->i] = '\0';
	ex->new = ft_free_strjoin(ex->new, &str[ex->l_exp]);
	while (env && (ft_strncmp(&str[ex->i + 1], env->cle, len) != 0
			|| len != (int)ft_strlen(env->cle)))
		env = env->next;
	if (ex->new && env)
		ex->new = ft_free_strjoin(ex->new, env->params);
	if (!ex->new)
		return ;
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
	str[ex->i] = '$';
	while (env && (ft_strcmp(sys, env->cle) != 0
			|| 16 != (int)ft_strlen(env->cle)))
		env = env->next;
	if (ex->new && env)
		ex->new = ft_free_strjoin(ex->new, env->params);
	if (!ex->new)
		return ;
	ex->l_exp = ex->i + 1 + 1;
	ex->i = ex->l_exp;
}

void	dollar_ask(char *str, t_exec *exec, t_exutils *ex)
{
	char	*nb;

	nb = ft_itoa(exec->error_code);
	if (!nb)
	{
		perror("Malloc");
		return ;
	}
	str[ex->i] = '\0';
	ex->new = ft_free_strjoin(ex->new, &str[ex->l_exp]);
	if (!ex->new)
	{
		(perror("Malloc"), free(nb));
		return ;
	}
	str[ex->i] = '$';
	ex->new = ft_free_strjoin(ex->new, nb);
	if (!ex->new)
	{
		(perror("Malloc"), free(nb));
		return ;
	}
	free(nb);
	ex->l_exp = ex->i + 1 + 1;
	ex->i = ex->l_exp;
}

void	expansion_two(t_exutils *ex, char *str, t_exec *exec)
{
	while (str[ex->i] && check_whitespace(str[ex->i]))
		ex->i++;
	ex->l_exp = ex->i;
	while (str[ex->i])
	{
		ex->quoted = is_quoted(ex->quoted, str[ex->i]);
		if (str[ex->i] == '$' && str[ex->i + 1] == '$'
			&& (ex->quoted != S_QUOTE || ex->is_here_doc))
			dollar_dollar(str, exec->env, ex);
		else if (str[ex->i] == '$' && str[ex->i + 1] == '?'
			&& (ex->quoted != S_QUOTE || ex->is_here_doc))
			dollar_ask(str, exec, ex);
		else if (str[ex->i] == '$' && (str[ex->i + 1] == '\''
				|| str[ex->i + 1] == '\"') && ex->quoted != NO_QUOTE)
			ex->i++;
		else if (str[ex->i] == '$' && check_whitespace(str[ex->i + 1]) != 1
			&& str[ex->i + 1] != '\0'
			&& str[ex->i + 1] != '/'
			&& (ex->quoted != S_QUOTE || ex->is_here_doc))
			add_expand(str, exec->env, ex);
		else
			ex->i++;
	}
}

// ligne ne commentaire peut etre inutile a ne pas effacer pour le moment 
char	*expansion(char *str, t_exec *exec, int is_here_doc)
{
	t_exutils	ex;
	char		c;

	ex.i = 0;
	ex.new = ft_calloc(1, 1);
	if (!ex.new)
		return (NULL);
	ex.quoted = NO_QUOTE;
	ex.is_here_doc = is_here_doc;
	while (str[ex.i] && str[ex.i] != '$'
		&& check_whitespace(str[ex.i + 1]) == 0 && ex.quoted != S_QUOTE)
	{
		ex.quoted = is_quoted(ex.quoted, str[ex.i]);
		ex.i++;
	}
	if (!str[ex.i])
		return (free(ex.new), str);
	if (str[ex.i] || str[ex.i] == '$')
	{
		c = str[ex.i];
		str[ex.i] = '\0';
		(free(ex.new), ex.new = ft_strdup(str));
		if (!ex.new)
			return (NULL);
		str[ex.i] = c;
	}
	expansion_two(&ex, str, exec);
	ex.new = ft_free_strjoin(ex.new, &str[ex.l_exp]);
	if (!ex.new)
		return (free(str), NULL);
	return (free(str), ex.new);
}
