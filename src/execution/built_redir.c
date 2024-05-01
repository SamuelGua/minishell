#include "minishell.h"


int built_out(t_file *file, int out2)
{
	int fd;

	if (file->redirec == GREAT)
		fd = open(file->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file->file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
		return (perror(file->file), 1);
	dup2(fd, out2);
	close(fd);
	return (0);
}

int built_in(t_file *file, int in2)
{
	int fd;

	fd = open(file->file, O_RDONLY);
	if (fd == -1)
		return (perror(file->file), 1);
	dup2(fd, in2);
	close(fd);
	return (0);
}

int built_redir(t_exec *exec, int out2, int in2)
{
	int	i;

	i = 0;
	while(exec->cmds->file && i != -1)
	{
		if (exec->cmds->file->redirec == GREAT
			|| exec->cmds->file->redirec == DGREAT)
			i = built_out(exec->cmds->file, out2);
		else if (exec->cmds->file->redirec == LESS)
			i = built_in(exec->cmds->file, in2);
		exec->cmds->file = exec->cmds->file->next;
	}
	return (i);
}