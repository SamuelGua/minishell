/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:07:31 by scely             #+#    #+#             */
/*   Updated: 2024/05/04 05:12:05 by scely            ###   ########.fr       */
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
# include <bits/sigaction.h>
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

typedef struct s_file
{
	char			*file;
	int				redirec;
	int				n_heredoc;
	int 			pipe; // 0 in && 1 out
	struct s_file *next;
} t_file;

typedef struct s_cmds
{
	char			**cmd; // {"ls", "-al", "Makefile", NULL}
	struct s_file	*file; // file avec redirection > >> << < |
	int				type; // 0 built-in | 1 cmds
	struct s_cmds 	*next;
} t_cmds;

typedef struct s_exec
{
	struct	s_token		*token;
	struct	s_env		*env;
	struct	s_export	*export;
	struct	s_cmds		*cmds;
	char				**exec_envp;
	char				*prompt;
	int					nb_pipe;
	int					pipe[2];
	int					previous_fd;
	int					error_code;
} t_exec;



//// INITIALISATION
// init env
t_env		*ft_lstnew_env(char *str1, char *str2);
void		ft_lstadd_back_env(t_env **lst, t_env *node);
t_env		*init_env(char **envp);
void		ft_free_env(t_env *env);

// init export
t_export	*init_export(t_env *env);
void		ft_free_export(t_export *export);

//// BUILT-IIN
int			ft_unset(t_export **export, t_env **env, char **str);
int			ft_env(t_env *env, char **str);
int			ft_echo(char **str); // retirer le $
int			ft_export(t_export **export, t_env **env, char **str, int i);
int			ft_pwd(void);
int			ft_exit(t_exec *exec);
int			ft_cd(t_env *env, char **str);


// EXPANSION
char		*expansion(char *str, t_exec *exec, int is_here_doc);
int			is_quoted(int quoted, char c);
int			is_valid_token(t_token *token);
char		*delete_quote(char *str);


t_cmds *build_cmd(t_exec *exec);
void	ft_lstadd_back_cmd(t_cmds **lst, t_cmds *node);
t_cmds	*ft_lstnew_cmd(char **cmd, t_file *file);
t_file	*ft_lstnew_file(char *file, int redirec);
void	ft_lstadd_back_file(t_file **lst, t_file *node);


int			builtin(t_exec *exec);
int			is_builtin(char **str);

int		execution(t_exec *exec);
char	**find_path(t_env *env);
int		nb_pipe(t_cmds *cmds);
int		wait_childs(int pid);

int		fd_out(t_file *file);
int		fd_in(t_file *file);
int		fd_pipe(t_file *file, t_exec *exec);
int		redirection(t_exec *exec);


void	ft_free_exec(t_exec* exec);
void	ft_free_cmd(t_cmds *cmd);
void	ft_free_file(t_file *file);

int		redirection(t_exec *exec);
void	run_here_doc(t_exec *exec);
void	clean_dir_temp(void);
int		find_here_doc(t_file *file);
void	print_lst_cmd(t_cmds *cmd);


//signaux
void	d_quite(int signal);
void	sig_c_interactive(struct sigaction *sig_struct);
void	c_new_prompt(int signal);
void	c_quite_exec(int signal);
void	sig_slash_interactive(struct sigaction *sig_struct);
void	slash_dump(int signal);
void	slash_exec(int signal);






#endif
