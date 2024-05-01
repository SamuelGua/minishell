#include "minishell.h"

void ft_free_file(t_file *file)
{
	t_file *tmp;

	while(file)
	{
		tmp = file;
		file = file->next;
		free(tmp);
	}
}

void ft_free_cmd(t_cmds *cmd)
{
	t_cmds *tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		ft_free(tmp->cmd);
		ft_free_file(tmp->file);
		free(tmp->file);
		free(tmp);
	}
}

void ft_free_exec(t_exec* exec)
{
	t_cmds *cmd_tmp;

	free_export(exec->export);
	ft_free_env(exec->env);
	while(exec->cmds)
	{
		cmd_tmp = exec->cmds;
		exec->cmds = exec->cmds->next;
		ft_free_cmd(cmd_tmp);
	}
}