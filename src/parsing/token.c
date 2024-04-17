/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:14:53 by scely             #+#    #+#             */
/*   Updated: 2024/04/17 11:31:49 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c, int stats)
{
	if (stats)
		return (0);
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	check_operator(char *str, int len)
{
	if (!ft_strncmp(str, ">>", len) || !ft_strncmp(str, "<<", len)
		|| !ft_strncmp(str, "||", len))
	{
		return (1);
	}
	return (0);
}

int	value_operator(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (DGREAT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (HERE_DOC);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (PIPE);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (LESS);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (GREAT);
	return (666);
}

// regle 5 pas prise en compte car elle sera traiter apres entre le parsing et l'execution
// regle 9 ne sera pas traiter car la gestion du # n'est pas demande par le sujet
t_token	*init_token(char *prompt)
{
	int		i = 0;
	int		quoted = NO_QUOTE;
	int		len = 1;
	t_token	*token = NULL;
	t_token	*node = NULL;
	int		type_token = 0;
	int		start_token = 0;
	int		sous_type = 1;

	while (1)
	{
		while (type_token == 0 && quoted == NO_QUOTE && prompt[i] == 32)
			i++;
		if (prompt[i] == '\0')
		{
			// regle 1
			if (type_token)
			{
				if (prompt[start_token] == '\'' || prompt[start_token] == '\"')
					sous_type = QUOTED;
				else if (is_operator(prompt[start_token], 0))
					sous_type = value_operator(&prompt[start_token]);
				else
					sous_type = UNQUOTED;
				printf("delimeter 1\n");
				node = ft_lstnew_token(&prompt[start_token], len, type_token, sous_type);
				ft_lstadd_back_token(&token, node);
				type_token = 0;
				sous_type = 1;
			}
			break ;
		}
		else if (type_token == OPERATOR && is_operator(prompt[i], quoted)
			&& check_operator(&prompt[start_token], len))
		{
			// regle 2
			len++;
		}
		else if (type_token == OPERATOR && check_operator(&prompt[start_token], len) == 0)
		{
			// regle 3
			printf("delimeter 3\n");
			node = ft_lstnew_token(&prompt[start_token], len, type_token, value_operator(&prompt[start_token]));
			ft_lstadd_back_token(&token, node);
			sous_type = 1;
			start_token = 0;
			type_token = 0;
			len = 1;
			i--;
		}
		else if (prompt[i] == '\'')
		{
			//relgle 4
			len++;
			if (quoted == NO_QUOTE)
			{
				quoted = S_QUOTE;
				if (i == 0 || (prompt[start_token] != '\"' && prompt[start_token] != '\'' && sous_type))
					start_token = i;
				type_token = WORD;
			} 
			else if (quoted == S_QUOTE)
				quoted = NO_QUOTE;
		}
		else if (prompt[i] == '\"' )
		{
			//relgle 4 bis
			len++;
			if (quoted == NO_QUOTE)
			{
				quoted = D_QUOTE;
				if (i == 0 || (prompt[start_token] != '\"' && prompt[start_token] != '\'' && sous_type))
					start_token = i;
				type_token = WORD;
			}
			else if (quoted == D_QUOTE)
				quoted = NO_QUOTE;
		}
		else if (is_operator(prompt[i], quoted))
		{
			// regle 6
			if (type_token != NO_TOKEN)
			{
				if (prompt[start_token] == '\'' || prompt[start_token] == '\"')
					sous_type = QUOTED;
				else if (is_operator(prompt[start_token], 0))
					sous_type = value_operator(&prompt[start_token]);
				else
					sous_type = UNQUOTED;
				printf("delimeter 6\n");
				node = ft_lstnew_token(&prompt[start_token], len, type_token, sous_type);
				ft_lstadd_back_token(&token, node);
				type_token = 0;
				sous_type = 1;
			}
			type_token = OPERATOR;
			start_token = i;
			len = 2;
		// len = 1;
		}
		else if (prompt[i] == ' ' && quoted == NO_QUOTE)
		{
			// regle 7
			if (prompt[start_token] == '\'' || prompt[start_token] == '\"')
				sous_type = QUOTED;
			else if (is_operator(prompt[start_token], 0))
				sous_type = value_operator(&prompt[start_token]);
			else
				sous_type = UNQUOTED;
			node = ft_lstnew_token(&prompt[start_token], len, type_token, sous_type);
			printf("delimeter 7\n");
			ft_lstadd_back_token(&token, node);
			sous_type = 1;
			type_token = 0;
			start_token = i;
			len = 1;
		}
		else if (type_token == WORD)
		{
			// regle 8
			len++;
		}
		else
		{
			//regle 10
			sous_type = 0;
			type_token = WORD;
			start_token = i;
			len++;
		}
		i++;
	}
	return (token);
}
