/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:52:14 by scely             #+#    #+#             */
/*   Updated: 2024/04/30 05:59:41 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// void builtin(t_cmds *cmd, t_env **env, t_export **export)
// {
// 		if (ft_strcmp(cmd->cmd[0], "env") == 0)
// 			ft_env(*env, cmd->cmd);
// 		else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
// 			ft_unset(export, env, cmd->cmd);
// 		else if (ft_strcmp(cmd->cmd[0], "echo") == 0)
// 			ft_echo(cmd->cmd++);
// 		else if (ft_strcmp(cmd->cmd[0], "export") == 0)
// 			ft_export(export, env, cmd->cmd, 0);
// 		else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)	
// 			ft_pwd();
// 		else if (ft_strcmp(cmd->cmd[0], "exit") == 0)	
// 			ft_exit(*env, *export, cmd->cmd);
// 		else if (ft_strcmp(cmd->cmd[0], "cd") == 0)		
// 			ft_cd(*env, cmd->cmd);
// }
void builtin(t_exec *exec)
{
		if (ft_strcmp(exec->cmds->cmd[0], "env") == 0)
			ft_env(exec->env, exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "unset") == 0)
			ft_unset(&exec->export, &exec->env, exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "echo") == 0)
			ft_echo(exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "export") == 0)
			ft_export(&exec->export, &exec->env, exec->cmds->cmd, 0);
		else if (ft_strcmp(exec->cmds->cmd[0], "pwd") == 0)	
			ft_pwd();
		else if (ft_strcmp(exec->cmds->cmd[0], "exit") == 0)	
			ft_exit(exec->env, exec->export, exec->cmds->cmd);
		else if (ft_strcmp(exec->cmds->cmd[0], "cd") == 0)		
			ft_cd(exec->env, exec->cmds->cmd);
}

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

int main(int ac, char **av, char **envp)
{
	char *prompt;
	(void)ac;
	(void)av;
	t_exec		exec;
	t_token 	*token = NULL;

	exec.env = init_env(envp);
 	exec.export = init_export(exec.env);
	exec.envp = envp;
	// if (env == NULL)
	// 	return (printf("Erreur malloc\n"), 2);
	while (1)
	{
		prompt = readline("\002\033[1;35mminishell > \033[0m\002");
		if (!prompt)
		{
			ft_free_env(exec.env);
			free_export(exec.export);
			return (2);
		}
		char **lol = ft_split(prompt, ' ');
		if (lol == NULL)
			continue ;
		else
			ft_free(lol);
		token = init_token(prompt, token);
		add_history(prompt);
		free(prompt);
		if (is_valid_token(token))
			continue;

		exec.cmds = build_cmd(token, exec.env);
		execution(&exec);
	}
	return (0);
}
