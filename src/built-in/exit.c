/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:18:18 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 13:10:33 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long int	ft_atoll(char *str)
{
	int				i;
	long long int	nbrs;

	i = 0;
	nbrs = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		nbrs = nbrs * 10 + str[i] - '0';
		i++;
	}
	if (str[0] == '-')
		nbrs *= -1;
	return (nbrs);
}

static int	size_nbrs(t_exec *exec, char *str, int *fd_origin)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		j++;
	while (ft_isdigit(str[i + j]))
		i++;
	if (str[i + j] == '\0')
		i--;
	if (ft_isdigit(str[i + j]) == 0 || i >= 19)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd(" numeric argument required\n", 2);
		ft_free_exec(exec);
		if(fd_origin) 
			(close(fd_origin[0]), close(fd_origin[1]));
		exit (2);
	}
	return (1);
}

int	ft_exit(t_exec *exec, int *fd_origin)
{
	int	i;

	i = 1;
	if (exec->cmds->cmd[1] == NULL)
	{
		if(fd_origin)
			(close(fd_origin[1]), close(fd_origin[0]));
		(ft_free_exec(exec), printf("exit\n"), exit(exec->error_code));
	}
	while (exec->cmds->cmd[i])
	{
		if (i >= 2)
		{
			ft_putstr_fd("exit\n", 2);
			print_message(NULL,  NULL, " too many arguments", 2);
			return (1);
		}
		i++;
	}
	i = 0;
	while (exec->cmds->cmd[++i])
		size_nbrs(exec, exec->cmds->cmd[i], fd_origin);
	ft_putstr_fd("exit\n", 2);
	if(exec->cmds->cmd[1])
		i = ft_atoll(exec->cmds->cmd[1]);
	ft_free_exec(exec);
	if(fd_origin)
		(close(fd_origin[0]), close(fd_origin[1]));
	if (i)
		exit(i);
	exit(0);
	return(666);
}
