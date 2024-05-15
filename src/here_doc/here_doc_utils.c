/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:55:56 by scely             #+#    #+#             */
/*   Updated: 2024/05/15 09:55:33 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (file->n_heredoc != 0)
		free(here_doc);
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

int	is_limiter(char *line, char *lim)
{
	if (!ft_strcmp(line, lim))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	check_quote_here(char *limiter)
{
	int	i;

	i = 0;
	while (limiter[i])
	{
		if (limiter[i] == '\'' || limiter[i] == '\"')
			return (QUOTED);
		i++;
	}
	return (0);
}
