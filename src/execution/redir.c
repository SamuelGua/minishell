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
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
int fd_in(t_file *file)
{
	int fd;

	fd = open(file->file, O_RDONLY);
	if (fd == -1)
		return (perror(file->file), 1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int fd_pipe(t_file *file, t_exec *exec)
{
	if (file->pipe == 0)
	{
		dup2(exec->previous_fd, STDIN_FILENO);
		close(exec->previous_fd);
		if (!exec->cmds->next)
			close(exec->pipe[1]);
	}
	else
	{
		dup2(exec->pipe[1], STDOUT_FILENO);
		close(exec->pipe[1]);
	}
	return (0);
}
