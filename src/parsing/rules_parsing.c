
#include "minishell.h"

void rules_one(t_token **token, t_parsutils *utils_pars, char *prompt)
{
	t_token	*node = NULL;

	if (utils_pars->type_token)
	{
		if (prompt[utils_pars->start_token] == '\'' || prompt[utils_pars->start_token] == '\"')
			utils_pars->sous_type = QUOTED;
		else if (is_operator(prompt[utils_pars->start_token], 0))
			utils_pars->sous_type = value_operator(&prompt[utils_pars->start_token]);
		else
			utils_pars->sous_type = UNQUOTED;
		printf("delimeter 1\n");
		node = ft_lstnew_token(&prompt[utils_pars->start_token], utils_pars->len, utils_pars->type_token, utils_pars->sous_type);
		ft_lstadd_back_token(token, node);
		utils_pars->type_token = 0;
		utils_pars->sous_type = 1;
	}
}

void rules_four(t_parsutils *utils_pars, char *prompt)
{
	if (prompt[utils_pars->i] == '\'')
	{
		if (utils_pars->quoted == NO_QUOTE)
			utils_pars->quoted = S_QUOTE;
		else if (utils_pars->quoted == S_QUOTE)
			utils_pars->quoted = NO_QUOTE;
	}
	else if (prompt[utils_pars->i] == '\"' )
	{
		if (utils_pars->quoted == NO_QUOTE)
			utils_pars->quoted = D_QUOTE;
		else if (utils_pars->quoted == D_QUOTE)
			utils_pars->quoted = NO_QUOTE;
	}
	if (utils_pars->i == 0 || (prompt[utils_pars->start_token] != '\"'
		&& prompt[utils_pars->start_token] != '\'' && utils_pars->sous_type))
	{
		utils_pars->start_token = utils_pars->i;
	}
	utils_pars->type_token = WORD;
	utils_pars->len++;
}

void	rules_three(t_token **token, t_parsutils *utils_pars, char *prompt)
{
	t_token	*node = NULL;

	printf("delimeter 3\n");
	node = ft_lstnew_token(&prompt[utils_pars->start_token], utils_pars->len, utils_pars->type_token, value_operator(&prompt[utils_pars->start_token]));
	ft_lstadd_back_token(token, node);
	utils_pars->sous_type = 1;
	utils_pars->start_token = utils_pars->i-1;
	utils_pars->type_token = 0;
	utils_pars->len = 1;
	utils_pars->i--;
}

void	rules_six(t_token **token, t_parsutils *utils_pars, char *prompt)
{
	t_token	*node = NULL;

	if (utils_pars->type_token != NO_TOKEN)
	{
		if (prompt[utils_pars->start_token] == '\'' || prompt[utils_pars->start_token] == '\"')
			utils_pars->sous_type = QUOTED;
		else if (is_operator(prompt[utils_pars->start_token], 0))
			utils_pars->sous_type = value_operator(&prompt[utils_pars->start_token]);
		else
			utils_pars->sous_type = UNQUOTED;
		printf("delimeter 6\n");
		node = ft_lstnew_token(&prompt[utils_pars->start_token], utils_pars->len, utils_pars->type_token, utils_pars->sous_type);
		ft_lstadd_back_token(token, node);
		utils_pars->type_token = 0;
		utils_pars->sous_type = 1;
	}
	utils_pars->type_token = OPERATOR;
	utils_pars->start_token = utils_pars->i;
	utils_pars->len = 2;
}

void	rules_seven(t_token **token, t_parsutils *utils_pars, char *prompt)
{
	t_token	*node = NULL;

	if (prompt[utils_pars->start_token] == '\'' || prompt[utils_pars->start_token] == '\"')
		utils_pars->sous_type = QUOTED;
	else if (is_operator(prompt[utils_pars->start_token], 0))
		utils_pars->sous_type = value_operator(&prompt[utils_pars->start_token]);
	else
		utils_pars->sous_type = UNQUOTED;
	node = ft_lstnew_token(&prompt[utils_pars->start_token], utils_pars->len, utils_pars->type_token, utils_pars->sous_type);
	printf("delimeter 7\n");
	ft_lstadd_back_token(token, node);
	utils_pars->sous_type = 1;
	utils_pars->type_token = 0;
	utils_pars->start_token = utils_pars->i;
	utils_pars->len = 1;
}
