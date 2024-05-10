/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:12:48 by scely             #+#    #+#             */
/*   Updated: 2024/05/10 13:44:35 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	start_expansion(t_exutils *ex, char *str)
{
	char		c;

	if (str[ex->i] || str[ex->i] == '$')
	{
		c = str[ex->i];
		str[ex->i] = '\0';
		(free(ex->new), ex->new = ft_strdup(str));
		if (!ex->new)
			return (1);
		str[ex->i] = c;
	}
	return (0);
}

// ligne ne commentaire peut etre inutile a ne pas effacer pour le moment 
char	*expansion(char *str, t_exec *exec, int is_here_doc)
{
	t_exutils	ex;

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
	if (start_expansion(&ex, str))
		return (NULL);
	expansion_two(&ex, str, exec);
	ex.new = ft_free_strjoin(ex.new, &str[ex.l_exp]);
	if (!ex.new)
		return (free(str), NULL);
	return (free(str), ex.new);
}
