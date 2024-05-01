#include "minishell.h"

typedef struct s_here_doc
{
	char *here_doc;
	char *new_file;
	char *nb_file;
} t_here_doc;

// fichier cacher les pour mettre les ficher des heredoc

int	fill_heredoc(int fd, char *limiter)
{
	char	*line;
	while (1)
	{
		// ft_putstr
		ft_putstr_fd("HERE_DOC > ",STDOUT_FILENO);
		line = get_next_line(0);
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		free(line);
	}
	return (0);
}

int here_doc(t_file *file)
{
	int	i;
	int fd;
	t_here_doc doc;

	i = 0;
	doc.here_doc = "here_doc";
	doc.new_file = NULL;
	if (access(doc.here_doc, F_OK) == -1)
		
	while (access(doc.new_file, F_OK) == -1)
	{
		if (doc.new_file)
			free(doc.new_file);
		doc.nb_file = ft_itoa(i);
		doc.new_file = ft_strjoin(doc.here_doc, doc.nb_file);
		printf("%s\n", doc.new_file);
		free(doc.nb_file);
		i++;
	}
	fd = open(doc.new_file, O_WRONLY | O_CREAT, 0644);
	free(doc.new_file);
	if (fd < 0)
		return (-1);
	fill_heredoc(fd, file->file);
	close(fd);
	return (0);
}
