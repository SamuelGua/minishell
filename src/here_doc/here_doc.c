/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 21:52:54 by scely             #+#    #+#             */
/*   Updated: 2024/05/10 14:30:53 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fichier cacher les pour mettre les ficher des heredoc
void	here_doc_sig(int dup_origin, char *lim, int i)
{
	dup2(dup_origin, STDIN_FILENO);
	close(dup_origin);
	if (i == 1)
		printf("\n");
	else if (i == 2)
	{
		printf("minishell: warning: here-document at line");
		printf(" 1 delimited by end-of-file (wanted `%s')\n", lim);
	}
	free(lim);
}

int	init_value_heredoc(int *type_quote, char *limiter, char **lim, int *dup_origin)
{
	*type_quote = check_quote_here(limiter);
	*lim = ft_strdup(limiter);
	if (!lim)
		return (1);
	*lim = delete_quote(*lim);
	if (!*lim)
		return (1);
	*dup_origin = dup(STDIN_FILENO);
	if (*dup_origin == -1)
		return (free(*lim), 1);
	signal_heredoc();
	return (0);
}

// 1 pour dans le heredoc
int	fill_heredoc(int fd, char *limiter, t_exec *exec)
{
	char	*line;
	char	*lim;
	int		type_quote;
	int		dup_origin;

	lim = NULL;
	if (init_value_heredoc(&type_quote, limiter, &lim, &dup_origin))
		return (-1);
	while (1 && g_exit_code != 5)
	{
		line = readline("HERE_DOC > ");
		if (!line && g_exit_code == 5)
			return (here_doc_sig(dup_origin, lim, 1), 130);
		if (!line)
			return (here_doc_sig(dup_origin, lim, 2), 1);
		if (is_limiter(line, lim))
			break ;
		if (type_quote == NO_QUOTE)
			line = expansion(line, exec, 1);
		(ft_putstr_fd(line, fd), ft_putstr_fd("\n", fd), free(line));
	}
	here_doc_sig(dup_origin, lim, 0);
	if (g_exit_code == 5)
		return (clean_dir_temp(), 130);
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
