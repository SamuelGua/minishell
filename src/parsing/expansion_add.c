/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:41:16 by scely             #+#    #+#             */
/*   Updated: 2024/05/10 13:42:42 by scely            ###   ########.fr       */
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
