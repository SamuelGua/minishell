#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>				// printf, perror
# include <stdlib.h>			// malloc, free, exit, getenv
# include <unistd.h>			// write, access, read, close, fork, chdir, getcwd, isatty, ttyname, ttyslot, dup, dup2, pipe, execve, tcsetattr, tcgetattr
# include <fcntl.h>				// open
# include <sys/wait.h>			// wait, waitpid, wait3, wait4
# include <signal.h>			// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>			// stat, lstat, fstat
# include <dirent.h>			// opendir, readdir, closedir
# include <string.h>			// strerror
# include <termios.h>			// ioctl
# include <readline/readline.h>	// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <curses.h>			// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// fonction list env
typedef struct s_env
{
	char			*cle; 
	char			*params;
	struct s_env	*next;
} t_env;

t_env	*ft_lstnew_env(char *str1, char *str2);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*init_env(char **envp);
void	ft_free_env(t_env *env);


//built-in
void	ft_unset(t_env **env, char **str);
void	ft_env(t_env *env);
void	ft_echo(t_env *env, char **str); // retirer le $
void 	ft_export(t_env **env, char **str);



#endif
