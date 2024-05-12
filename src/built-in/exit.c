/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:18:18 by scely             #+#    #+#             */
/*   Updated: 2024/05/12 16:44:40 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limit(char *str)
{
	int						i;
	unsigned long long int	nbrs;
	unsigned long long int	max_64;

	i = 0;
	nbrs = 0;
	max_64 = INT64_MAX;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		nbrs = nbrs * 10 + str[i] - '0';
		i++;
	}
	if (nbrs == max_64 + 1 && str[0] == '-')
		return (0);
	else if (nbrs > INT64_MAX)
		return (1);
	return (0);
}

static void	dflt_fd(int *fd_origin)
{
	if (!fd_origin)
		return ;
	if (fd_origin[1] != -1)
	{
		if (dup2(fd_origin[1], STDOUT_FILENO) == -1)
			perror("dup2");
		close(fd_origin[1]);
	}
	if (fd_origin[0] != -1)
	{
		if (dup2(fd_origin[0], STDIN_FILENO) == -1)
			perror("dup2");
		close(fd_origin[0]);
	}
}

static int	size_nbrs(t_exec *exec, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		j++;
	while (ft_isdigit(str[i + j]))
		i++;
	if (str[i + j] != '\0' || i > 19 || check_limit(str))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		ft_free_exec(exec);
		rl_clear_history();
		exit(2);
	}
	return (1);
}

int	ft_exit(t_exec *exec, int *fd_origin, int is_pipe)
{
	long long int	i;

	if (is_pipe)
		ft_putstr_fd("exit\n", 1);
	dflt_fd(fd_origin);
	if (exec->cmds->cmd[1] == NULL)
	{
		ft_free_exec(exec);
		rl_clear_history();
		exit(exec->error_code);
	}
	i = 0;
	while (exec->cmds->cmd[++i])
	{
		if (i >= 2)
		{
			print_message(NULL, "minishell ", "exit: too many arguments", 2);
			return (1);
		}
		size_nbrs(exec, exec->cmds->cmd[i]);
	}
	i = ft_atoll(exec->cmds->cmd[1]);
	rl_clear_history();
	ft_free_exec(exec);
	exit(i);
}
