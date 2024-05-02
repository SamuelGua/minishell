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
	char	*lim;

	while (1)
	{
		ft_putstr_fd("HERE_DOC {",STDOUT_FILENO);
		ft_putstr_fd(limiter,STDOUT_FILENO);
		ft_putstr_fd("} > ",STDOUT_FILENO);
		line = get_next_line(0);
		lim = strchr(line,'\n');
		*lim = '\0';
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			break ;
		}
		*lim = '\n';
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

	i = 1;
	doc.here_doc = "src/here_doc/.tmp_here_doc/here_doc";
	doc.new_file = ft_strdup(doc.here_doc);
	while (access(doc.new_file, F_OK) == 0)
	{
		if (doc.new_file)
			free(doc.new_file);
		doc.nb_file = ft_itoa(i);
		doc.new_file = ft_strjoin(doc.here_doc, doc.nb_file);;
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

void run_here_doc(t_exec *exec)
{
	t_cmds *tmp;

	tmp = exec->cmds;
	while (tmp)
	{
		while (tmp->file)
		{
			if (tmp->file->redirec == HERE_DOC)
				here_doc(tmp->file);
			tmp->file = tmp->file->next;
		}
		tmp = tmp->next;
	}
}
