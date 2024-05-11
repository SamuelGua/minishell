/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:07:31 by scely             #+#    #+#             */
/*   Updated: 2024/05/11 11:58:11 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "parsing.h"
// # include <bits/sigaction.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

#define PATH_HERE "src/here_doc/tmp_here_doc/here_doc";

extern int			g_exit_code;

// Structure env et export
typedef struct s_env
{
	char			*cle;
	char			*params;
	struct s_env	*next;
}					t_env;

typedef struct s_export
{
	char			*cle;
	char			*params;
	struct s_export	*left;
	struct s_export	*right;
}					t_export;

//  PIPE 0 in && 1 out
typedef struct s_file
{
	char			*file;
	int				redirec;
	int				n_heredoc;
	int				pipe;
	struct s_file	*next;
}					t_file;

// TYPE 0 built-in | 1 cmds
typedef struct s_cmds
{
	char			**cmd;
	struct s_file	*file;
	int				type;
	struct s_cmds	*next;
}					t_cmds;

typedef struct s_exec
{
	struct s_token	*token;
	struct s_env	*env;
	struct s_export	*export;
	struct s_cmds	*cmds;
	char			**exec_envp;
	char			*prompt;
	int				nb_pipe;
	int				pipe[2];
	int				previous_fd;
	int				error_code;
}					t_exec;

typedef struct s_cdutils
{
	t_env			*pwd;
	t_env			*oldpwd;
	char			*previous_pwd;
}					t_cdutils;

typedef struct s_expand
{
	int				i;
	char			*new;
	int				l_exp;
	int				quoted;
	int				is_here_doc;

}					t_exutils;

typedef struct s_build_cmd
{
	t_cmds			*cmds_tmp;
	t_token			*end;
	t_cmds			*cmds;
	t_token			*tmp;
	int				nb_here_doc;
}					t_build_cmd;

typedef struct s_here_doc
{
	char	*here_doc;
	char	*new_file;
	char	*nb_file;
}			t_here_doc;

//// INITIALISATION
// init env
t_env				*ft_lstnew_env(char *str1, char *str2);
void				ft_lstadd_back_env(t_env **lst, t_env *node);
t_env				*init_env(char **envp);
void				ft_free_env(t_env *env);

// init export
t_export			*init_export(t_env *env);
void				ft_free_export(t_export *export);

//// BUILT-IIN
int					ft_unset(t_export **export, t_env **env, char **str);
int					ft_env(t_env *env, char **str);
int					ft_echo(char **str);
int					ft_export(t_export **export, t_env **env, char **str,
						int i);
int					ft_pwd(void);
int					ft_exit(t_exec *exec, int *fd_origin, int is_pipe);
int					ft_cd(t_env *env, char **str);

// EXPANSION
char				*expansion(char *str, t_exec *exec, int is_here_doc);
int					is_quoted(int quoted, char c);
int					is_valid_token(t_token *token);
char				*delete_quote(char *str);
void	add_expand(char *str, t_env *env, t_exutils *ex);
void	dollar_dollar(char *str, t_env *env, t_exutils *ex);
void	dollar_ask(char *str, t_exec *exec, t_exutils *ex);


void				pipe_init(t_file *tmp_file, t_token *end, t_cmds *cmds,
						int i);
char				**node_init(t_token *tmp, t_file *tmp_file, t_cmds *cmds, t_build_cmd *utils);
t_cmds				*build_cmd(t_exec *exec);
void				ft_lstadd_back_cmd(t_cmds **lst, t_cmds *node);
t_cmds				*ft_lstnew_cmd(char **cmd, t_file *file);
t_file				*ft_lstnew_file(char *file, int redirec);
void				ft_lstadd_back_file(t_file **lst, t_file *node);
t_cmds				*create_node(t_token *tmp, t_build_cmd *utils);
//exec
int	check_isfile(t_exec *exec);
int	valid_cmd(t_exec *exec, char **path);
int	check_errors(t_exec *exec, char **path);


int					builtin(t_exec *exec, int *fd_origin, int is_pipe);
int					is_builtin(char **str);

int					execution(t_exec *exec);
char				**find_path(t_env *env);
int					nb_pipe(t_cmds *cmds);
int					wait_childs(int pid);
void				print_message(char *str1, char *str2, char *str3, int fd);
char				**build_envp(t_env *env);

int					fd_out(t_file *file);
int					fd_in(t_file *file);
int					fd_pipe(t_file *file, t_exec *exec);
int					redirection(t_exec *exec);

void				ft_free_exec(t_exec *exec);
void				ft_free_cmd(t_cmds *cmd);
void				ft_free_file(t_file *file);
int					cmds_size(t_token *tmp, t_token *end);
void				set_nbs(t_token *tmp, t_file *file, t_build_cmd *utl);


int					redirection(t_exec *exec);
int					run_here_doc(t_exec *exec);
void				clean_dir_temp(void);
int					find_here_doc(t_file *file);

// signaux
void				signal_interactive(void);
void				signal_exec(void);
void				signal_heredoc(void);

int		find_here_doc(t_file *file);
void	clean_dir_temp(void);
int		is_limiter(char *line, char *lim);
int		check_quote_here(char *limiter);



#endif
