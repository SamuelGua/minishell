/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:07:31 by scely             #+#    #+#             */
/*   Updated: 2024/04/10 15:26:16 by scely            ###   ########.fr       */
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

// fonction list env
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
void	ft_lstadd_back_env(t_env **lst, t_env *new);
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


#endif
