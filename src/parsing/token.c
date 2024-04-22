/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:14:53 by scely             #+#    #+#             */
/*   Updated: 2024/04/22 09:18:58 by scely            ###   ########.fr       */
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
	if (!ft_strncmp(str, ">>", len) || !ft_strncmp(str, "<<", len))
		return (1);
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

void	init_token_two(t_token **token, t_parsutils *utils_pars, char *prompt)
{
	if (prompt[utils_pars->i] == '\'' || prompt[utils_pars->i] == '\"')
		rules_four(utils_pars, prompt);
	else if (is_operator(prompt[utils_pars->i], utils_pars->quoted))
		rules_six(token, utils_pars, prompt);
	else if (prompt[utils_pars->i] == ' ' && utils_pars->quoted == NO_QUOTE)
		rules_seven(token, utils_pars, prompt);
	else if (utils_pars->type_token == WORD)
		utils_pars->len++;
	else
	{
		utils_pars->sous_type = 0;
		utils_pars->type_token = WORD;
		utils_pars->start_token = utils_pars->i;
		utils_pars->len++;
	}
}

t_token	*init_token(char *prompt)
{
	t_token		*token;
	t_parsutils	utils_pars;

	(value_pars_init(&utils_pars), token = NULL);
	while (1)
	{
		while (utils_pars.type_token == 0 && utils_pars.quoted == NO_QUOTE
			&& check_whitespace(prompt[utils_pars.i]))
				utils_pars.i++;
		if (prompt[utils_pars.i] == '\0')
		{
			rules_one(&token, &utils_pars, prompt);
			break ;
		}
		else if (utils_pars.type_token == OPERATOR && is_operator(prompt[utils_pars.i], utils_pars.quoted)
			&& check_operator(&prompt[utils_pars.start_token], utils_pars.len))
				utils_pars.len++;
		else if (utils_pars.type_token == OPERATOR && check_operator(&prompt[utils_pars.start_token], utils_pars.len) == 0)
			rules_three(&token, &utils_pars, prompt);
		else
			init_token_two(&token, &utils_pars, prompt);
		utils_pars.i++;
	}
	return (token);
}
