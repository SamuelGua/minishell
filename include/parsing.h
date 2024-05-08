/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:41:51 by scely             #+#    #+#             */
/*   Updated: 2024/04/25 19:27:23 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

// TOKEN
# define WORD 10
# define OPERATOR 20
# define QUOTED 1
# define UNQUOTED 2
# define GREAT 3 // >
# define DGREAT 4 // >>
# define LESS 5 // <
# define HERE_DOC 6 // <<
# define PIPE 7 // |

//// PARSING
# define NO_QUOTE 0
# define S_QUOTE 1
# define D_QUOTE 2
# define NO_TOKEN 0


typedef struct s_parsing_utils
{
	int	i;
	int	quoted;
	int	len;
	int	type_token;
	int	start_token;
	int	sous_type;
}	t_parsutils;

//
typedef struct s_token
{
	char			*str;
	int				token; // 1 2 3 4 5 6 7
	int				type; // 10 20
	struct s_token	*next;
}	t_token;

// token utils
t_token	*ft_lstnew_token(char *str, int len, int type, int token);
void	ft_lstadd_back_token(t_token **token, t_token *node);
t_token	*init_token(char *prompt, t_token *token);
void	print_token(t_token *token);
void	free_token(t_token *token);

// creat token
void	value_pars_init(t_parsutils *utils_pars);
void	rules_one(t_token **token, t_parsutils *utils_pars, char *prompt);
void	rules_three(t_token **token, t_parsutils *utils_pars, char *prompt);
void	rules_four(t_parsutils *utils_pars, char *prompt);
void	rules_six(t_token **token, t_parsutils *utils_pars, char *prompt);
void	rules_seven(t_token **token, t_parsutils *utils_pars, char *prompt);

int		is_operator(char c, int stats);
int		check_operator(char *str, int len);
int		value_operator(char *str);
int		check_whitespace(char c);
int		is_builtin(char **str);

#endif