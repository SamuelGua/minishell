#include "minishell.h"

void ft_free_file(t_file *file)
{
	t_file *tmp;

	while(file)
	{
		tmp = file;
		file = file->next;
		free(tmp->file);
		free(tmp);
	}
}

void ft_free_cmd(t_cmds *cmd)
{
	ft_free(cmd->cmd);
	ft_free_file(cmd->file);
	free(cmd);
}

void ft_free_exec(t_exec* exec)
{
	t_cmds *tmp_cmd;


	ft_free_export(exec->export);
	ft_free_env(exec->env);
	exec->export = NULL;
	exec->env = NULL;
	while (exec->cmds)
	{
		tmp_cmd = exec->cmds;
		exec->cmds = exec->cmds->next;
		ft_free_cmd(tmp_cmd);
	}
	exec->cmds = NULL;
}