/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:52:54 by scely             #+#    #+#             */
/*   Updated: 2024/05/09 21:53:44 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_here_doc
{
	char	*here_doc;
	char	*new_file;
	char	*nb_file;
}			t_here_doc;

#define PATH_HERE "src/here_doc/tmp_here_doc/here_doc";

// fichier cacher les pour mettre les ficher des heredoc
int	check_quote_here(char *limiter)
{
	if (*limiter == '\'')
		return (S_QUOTE);
	else if (*limiter == '\"')
		return (D_QUOTE);
	return (NO_QUOTE);
}

void	signal_c_heredoc(int signal_code)
{
	g_exit_code = 5;
	(void)signal_code;
	close(0);
}

void	signal_heredoc(void)
{
	struct sigaction	c_signal;

	c_signal.sa_handler = signal_c_heredoc;
	c_signal.sa_flags = 0;
	sigemptyset(&c_signal.sa_mask);
	sigaction(SIGINT, &c_signal, NULL);
}

// 1 pour dans le heredoc
int	fill_heredoc(int fd, char *limiter, t_exec *exec)
{
	char	*line;
	char	*lim;
	int		type_quote;
	int		dup_origin;

	type_quote = check_quote_here(limiter);
	lim = ft_strdup(limiter);
	lim = delete_quote(lim);
	dup_origin = dup(STDIN_FILENO);
	signal_heredoc();
	while (1 && g_exit_code != 5)
	{
		line = readline("HERE_DOC > ");
		if (!line && g_exit_code == 5)
		{
			dup2(dup_origin, STDIN_FILENO);
			close(dup_origin);
			free(lim);
			printf("\n");
			return (130);
		}
		if (!line)
		{
			dup2(dup_origin, STDIN_FILENO);
			close(dup_origin);
			free(line);
			printf("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `%s')\n",
				lim);
			free(lim);
			return (1);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		if (!ft_strcmp(line, lim))
		{
			free(line);
			break ;
		}
		(void)exec;
		if (type_quote == NO_QUOTE)
			line = expansion(line, exec, 1);
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(lim);
	if (g_exit_code == 5)
	{
		clean_dir_temp();
		return (130);
	}
	return (0);
}

int	here_doc(t_file *file, t_exec *exec)
{
	int			i;
	int			fd;
	t_here_doc	doc;

	i = 1;
	doc.here_doc = PATH_HERE;
	doc.new_file = ft_strdup(doc.here_doc);
	while (access(doc.new_file, F_OK) == 0)
	{
		if (doc.new_file)
			free(doc.new_file);
		doc.nb_file = ft_itoa(i);
		doc.new_file = ft_strjoin(doc.here_doc, doc.nb_file);
		;
		free(doc.nb_file);
		i++;
	}
	fd = open(doc.new_file, O_WRONLY | O_CREAT, 0644);
	free(doc.new_file);
	if (fd < 0)
		return (-1);
	i = fill_heredoc(fd, file->file, exec);
	close(fd);
	return (i);
}

int	run_here_doc(t_exec *exec)
{
	t_cmds	*tmp;
	t_file	*tmp_file;
	int		error_code;

	error_code = 0;
	tmp = exec->cmds;
	while (tmp)
	{
		tmp_file = tmp->file;
		while (tmp_file && error_code != 130)
		{
			if (tmp_file->redirec == HERE_DOC)
				error_code = here_doc(tmp_file, exec);
			tmp_file = tmp_file->next;
		}
		tmp = tmp->next;
	}
	return (error_code);
}

int	find_here_doc(t_file *file)
{
	char	*here_doc;
	char	*nb_file;
	int		fd;

	here_doc = PATH_HERE;
	if (file->n_heredoc != 0)
	{
		nb_file = ft_itoa(file->n_heredoc);
		here_doc = ft_strjoin(here_doc, nb_file);
		free(nb_file);
	}
	fd = open(here_doc, O_RDONLY, 0644);
	if (fd == -1)
		return (perror("error here_doc"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), -1);
	close(fd);
	return (0);
}

void	clean_dir_temp(void)
{
	char	*path;
	char	*path_bis;
	char	*nb_file;
	int		i;

	path = PATH_HERE;
	path_bis = ft_strdup(path);
	i = 1;
	while (access(path_bis, F_OK) == 0)
	{
		unlink(path_bis);
		free(path_bis);
		nb_file = ft_itoa(i);
		path_bis = ft_strjoin(path, nb_file);
		free(nb_file);
		i++;
	}
	free(path_bis);
}
