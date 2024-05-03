#include "minishell.h"

int fd_out(t_file *file)
{
	int fd;

	if (file->redirec == GREAT)
		fd = open(file->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (perror(file->file), 1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("dup2"), 1);
	close(fd);
	return (0);
}
int fd_in(t_file *file)
{
	int fd;

	fd = open(file->file, O_RDONLY);
	if (fd == -1)
		return (perror(file->file), 1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), 1);
	close(fd);
	return (0);
}

int fd_pipe(t_file *file, t_exec *exec)
{
	if (file->pipe == 0)
	{
		if (dup2(exec->previous_fd, STDIN_FILENO) == -1)
			return (perror("dup2"), 1);
		close(exec->previous_fd);
		if (!exec->cmds->next)
			close(exec->pipe[1]);
	}
	else
	{
		if (dup2(exec->pipe[1], STDOUT_FILENO) == -1)
			return (perror("dup2"), 1);
		close(exec->pipe[1]);
	}
	return (0);
}

int redirection(t_exec *exec)
{
	int	i;
	t_file *file;

	file = exec->cmds->file;
	i = 0;
	while (file && i != -1)
	{
		if (file->redirec == GREAT
			|| file->redirec == DGREAT)
			i = fd_out(file);
		else if (file->redirec == LESS)
			i = fd_in(file);
		else if (file->redirec == PIPE)
			i = fd_pipe(file, exec);
		else if (file->redirec == HERE_DOC)
			i = find_here_doc(file);
		file = file->next;
	}
	return (i);
}
