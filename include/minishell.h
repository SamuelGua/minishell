/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:07:31 by scely             #+#    #+#             */
/*   Updated: 2024/04/29 23:35:26 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
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
# include <errno.h>

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
t_env		*ft_lstnew_env(char *str1, char *str2);
void		ft_lstadd_back_env(t_env **lst, t_env *node);
t_env		*init_env(char **envp);
void		ft_free_env(t_env *env);

// init export
t_export	*init_export(t_env *env);
void		free_export(t_export *export);

//// BUILT-IIN
void		ft_unset(t_export **export, t_env **env, char **str);
void		ft_env(t_env *env, char **str);
void		ft_echo(char **str); // retirer le $
void		ft_export(t_export **export, t_env **env, char **str, int i);
void		ft_pwd(void);
int			ft_exit(t_env *env, t_export *export, char **str);
void		ft_cd(t_env *env, char **str);

// EXPANSION
char		*expansion(char *str, t_env *env);
int			is_quoted(int quoted, char c);
int			is_valid_token(t_token *token);
char		*delete_quote(char *str);

typedef struct s_file
{
	char	*file;
	int		redirec;
	int 	pipe; // 0 in && 1 out
	struct s_file *next;
} t_file;

typedef struct s_cmds
{
	char			**cmd; // {"ls", "-al", "Makefile", NULL}
	struct s_file	*file; // file avec redirection > >> << < |
	int				type; // 0 built-in | 1 cmds
	struct s_cmds 	*next;
} t_cmds;

t_cmds *build_cmd(t_token *token, t_env *env);
void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *node);
t_cmds	*ft_lstnew_cmd(char **cmd, t_file *file);
t_file	*ft_lstnew_file(char *file, int redirec);
void	ft_lstadd_back_file(t_file **lst, t_file *node);

typedef struct s_exec
{
	struct	s_env		*env;
	struct	s_export	*export;
	struct	s_cmds		*cmds;
	int					nb_pipe;
	int					pipe[2];
	int					previous_fd;
} t_exec;


void execution(t_exec *exec);
int fd_out(t_file *file);
int fd_in(t_file *file);
int fd_pipe(t_file *file, t_exec *exec);


void	print_lst_cmd(t_cmds *cmd);

#endif
