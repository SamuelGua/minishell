#include "minishell.h"

typedef struct s_here_doc
{
	char *here_doc;
	char *new_file;
	char *nb_file;
} t_here_doc;

# define PATH_HERE "src/here_doc/tmp_here_doc/here_doc";

// fichier cacher les pour mettre les ficher des heredoc

int check_quote_here(char *limiter)
{
	if (*limiter == '\'')
		return (S_QUOTE);
	else if (*limiter == '\"')
		return (D_QUOTE);
	return (NO_QUOTE);
}

int	fill_heredoc(int fd, char *limiter, t_exec *exec)
{
	char	*line;
	char	*c = NULL;
	char	*lim;
	int		type_quote;
	
	type_quote = check_quote_here(limiter);
	lim = delete_quote(limiter);
	while (1)
	{
		print_message("HERE_DOC {", lim, "} > ", 1);
		line = get_next_line(0);
		if (!line)
			return (666);
		c = strchr(line,'\n');
		*c = '\0';
		if (!ft_strcmp(line, lim))
		{
			free(line);
			break ;
		}
		*c = '\n';
		(void)exec;
		if (type_quote == NO_QUOTE)
			line = expansion(line, exec, 1); // 1 pour dans le heredoc
		ft_putstr_fd(line, fd);
		free(line);
	}
	return (0);
}

int here_doc(t_file *file, t_exec *exec)
{
	int	i;
	int fd;
	t_here_doc doc;

	i = 1;
	doc.here_doc = PATH_HERE;
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

	fill_heredoc(fd, file->file, exec);
	close(fd);
	return (0);
}

int run_here_doc(t_exec *exec)
{
	t_cmds *tmp;

	t_file *tmp_file;
	tmp = exec->cmds;
	while (tmp)
	{
		tmp_file = tmp->file;
		while (tmp_file)
		{
			if (tmp_file->redirec == HERE_DOC)
				here_doc(tmp_file, exec);
			tmp_file = tmp_file->next;
		}
		tmp = tmp->next;
	}
	return (0);
}


int find_here_doc(t_file *file)
{
	char *here_doc;
	char *nb_file;
	int fd;

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

void clean_dir_temp(void)
{
	char *path = PATH_HERE;

	char *path_bis = ft_strdup(path);
	char *nb_file;
	int i = 1;
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