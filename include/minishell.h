/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:07:31 by scely             #+#    #+#             */
/*   Updated: 2024/04/12 12:26:17 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <readline/readline.h>	
# include <readline/history.h>	
# include <curses.h>

//TOKEN
#define WORD 10
#define OPERATOR 20
#define QUOTED 1
#define UNQUOTED 2
#define GREAT 3
#define DGREAT 4
#define LESS 5
#define HERE_DOC 6
#define PIPE 7
#define AND_IF 8
#define OR_IF 9
#define LBRAKET 10
#define	RBRAKET 11

// Structure env et export
typedef struct s_env
{
	char			*cle;
	char			*params;
	struct s_env	*next;
}	t_env;

typedef struct s_export
{
	char			*cle;
	char			*params;
	struct s_export	*left;
	struct s_export	*right;
}	t_export;

//// INITIALISATION
// init env
t_env	*ft_lstnew_env(char *str1, char *str2);
void	ft_lstadd_back_env(t_env **lst, t_env *node);
t_env	*init_env(char **envp);
void	ft_free_env(t_env *env);

// init export
t_export *init_export(t_env *env);
void	free_export(t_export *export);

//// BUILT-IIN
void	ft_unset(t_export **export, t_env **env, char **str);
void	ft_env(t_env *env, char **str);
void	ft_echo(char **str); // retirer le $
void	ft_export(t_export **export, t_env **env, char **str);
void	ft_pwd(void);
int		ft_exit(t_env *env, t_export *export, char **str);
void	ft_cd(t_env *env, char **str);

//// PARSING
// Structure
typedef struct s_token
{
	char			*str;
	int				type;
	int				token;
	struct s_token	*next;
}	t_token;

t_token	*ft_lstnew_token(char *str, int len, int type, int token);
void	ft_lstadd_back_token(t_token **token, t_token *node);
t_token	*init_token(char *prompt);
void	print_token(t_token *token);
void free_token(t_token *token);

typedef struct s_operateur
{
	int	quoted;
	int	d_quoted;
	int	lbraket;
	int	rbraket;
	
}	t_operateur;


// init struct


#endif
