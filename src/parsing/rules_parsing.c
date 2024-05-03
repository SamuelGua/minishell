/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 09:19:14 by scely             #+#    #+#             */
/*   Updated: 2024/05/03 19:54:27 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rules_one(t_token **token, t_parsutils *utils, char *prompt)
{
	t_token	*node;

	node = NULL;
	if (utils->type_token)
	{
		if (prompt[utils->start_token] == '\''
			|| prompt[utils->start_token] == '\"')
			utils->sous_type = QUOTED;
		else if (is_operator(prompt[utils->start_token], 0))
			utils->sous_type = value_operator(&prompt[utils->start_token]);
		else
			utils->sous_type = UNQUOTED;
		node = ft_lstnew_token(&prompt[utils->start_token],
				utils->len, utils->type_token, utils->sous_type);
		if (!node)
			return ;
		ft_lstadd_back_token(token, node);
		utils->type_token = 0;
		utils->sous_type = 1;
	}
}

void	rules_four(t_parsutils *utils, char *prompt)
{
	if (prompt[utils->i] == '\'')
	{
		if (utils->quoted == NO_QUOTE)
			utils->quoted = S_QUOTE;
		else if (utils->quoted == S_QUOTE)
			utils->quoted = NO_QUOTE;
	}
	else if (prompt[utils->i] == '\"' )
	{
		if (utils->quoted == NO_QUOTE)
			utils->quoted = D_QUOTE;
		else if (utils->quoted == D_QUOTE)
			utils->quoted = NO_QUOTE;
	}
	if (utils->i == 0 || (prompt[utils->start_token] != '\"'
			&& prompt[utils->start_token] != '\'' && utils->sous_type))
	{
		utils->start_token = utils->i;
	}
	utils->type_token = WORD;
	utils->len++;
}

void	rules_three(t_token **token, t_parsutils *utils_pars, char *prompt)
{
	t_token	*node;

	node = NULL;
	node = ft_lstnew_token(&prompt[utils_pars->start_token],
			utils_pars->len, utils_pars->type_token,
			value_operator(&prompt[utils_pars->start_token]));
	if (!node)
		return ;
	ft_lstadd_back_token(token, node);
	utils_pars->sous_type = 1;
	utils_pars->start_token = utils_pars->i - 1;
	utils_pars->type_token = 0;
	utils_pars->len = 1;
	utils_pars->i--;
}

void	rules_six(t_token **token, t_parsutils *utils, char *prompt)
{
	t_token	*node;

	node = NULL;
	if (utils->type_token != NO_TOKEN)
	{
		if (prompt[utils->start_token] == '\''
			|| prompt[utils->start_token] == '\"')
			utils->sous_type = QUOTED;
		else if (is_operator(prompt[utils->start_token], 0))
			utils->sous_type = value_operator(&prompt[utils->start_token]);
		else
			utils->sous_type = UNQUOTED;
		node = ft_lstnew_token(&prompt[utils->start_token],
				utils->len, utils->type_token, utils->sous_type);
			if (!node)
				return ;
		ft_lstadd_back_token(token, node);
		utils->type_token = 0;
		utils->sous_type = 1;
	}
	utils->type_token = OPERATOR;
	utils->start_token = utils->i;
	utils->len = 2;
}

void	rules_seven(t_token **token, t_parsutils *utils, char *prompt)
{
	t_token	*node;

	node = NULL;
	if (prompt[utils->start_token] == '\''
		|| prompt[utils->start_token] == '\"')
		utils->sous_type = QUOTED;
	else if (is_operator(prompt[utils->start_token], 0))
		utils->sous_type = value_operator(&prompt[utils->start_token]);
	else
		utils->sous_type = UNQUOTED;
	node = ft_lstnew_token(&prompt[utils->start_token], utils->len,
			utils->type_token, utils->sous_type);
	if (!node)
		return ;
	ft_lstadd_back_token(token, node);
	utils->sous_type = 1;
	utils->type_token = 0;
	utils->start_token = utils->i;
	utils->len = 1;
}
