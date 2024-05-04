/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:18:18 by scely             #+#    #+#             */
/*   Updated: 2024/05/04 04:38:43 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retour d'erreur minishell ou bash

// ====>>>>
// bash-5.1$ exit 
// exit
// echo $? 0
// sort du bash


// si je fait exit sans arguments qui precede un 
//       commade qui a rate, je dois retourner se nombre

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
	if (str[i + j] == '\0')
		i--;
	if (ft_isdigit(str[i + j]) == 0 || i >= 19)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", str);
		ft_free_exec(exec);
		exit (2);
	}
	return (1);
}

int	ft_exit(t_exec *exec)
{
	int	i;

	i = 1;
	if (exec->cmds->cmd[0] == NULL)
	{
		ft_free_exec(exec);
		printf("exit\n");
		exit(0);
	}
	while (exec->cmds->cmd[i] && size_nbrs(exec, exec->cmds->cmd[i]))
		i++;
	if (i > 1)
	{
		printf("exit\n");
		return (printf("minishell: exit: too many arguments\n"), 1);
	}
	printf("exit\n");
	if(exec->cmds->cmd[1])
		i = ft_atoll(exec->cmds->cmd[1]);
	ft_free_exec(exec);
	// revoir la condition (exit 0 , exit ) pas le meme retour en fonction du dernier code erreur
	if (i)
		exit(i);
	else
		exit(0); // dernier code status
}
