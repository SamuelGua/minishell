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
int check_limit(char *str)
{
	int				i;
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

static void dflt_fd(int *fd_origin)
{
	dup2(fd_origin[1], STDOUT_FILENO);
	dup2(fd_origin[0] , STDIN_FILENO);
	close(fd_origin[1]);
	close(fd_origin[0] );
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

	if (str[i + j] != '\0' || i > 19 
		|| check_limit(str))
	{
		// printf("%d\n", (int)ft_strlen(str));
		// printf("%c\n", str[i + j]);
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("numeric argument required\n", 2);
		ft_free_exec(exec);
		dflt_fd(fd_origin);
		exit(2);
	}
	return (1);
}

int	ft_exit(t_exec *exec, int *fd_origin)
{
	long long int	i;

	if (exec->cmds->cmd[1] == NULL)
	{
		dflt_fd(fd_origin);
		(ft_free_exec(exec), ft_putstr_fd("exit\n", 2), exit(exec->error_code));
	}
	i = 0;
	while (exec->cmds->cmd[++i])
	{
		if (i >= 2)
		{
			ft_putstr_fd("exit\n", 2);
			print_message(NULL, NULL, "too many arguments", 2);
			return (1);
		}
		size_nbrs(exec, exec->cmds->cmd[i], fd_origin);
	}
	ft_putstr_fd("exit\n", 2);
	if(exec->cmds->cmd[1])
		i = ft_atoll(exec->cmds->cmd[1]);
	ft_free_exec(exec);
	dflt_fd(fd_origin);
	if (i)
		exit(i);
	exit(0);
	return(666);
}
