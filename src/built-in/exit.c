/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:18:18 by scely             #+#    #+#             */
/*   Updated: 2024/04/17 08:56:28 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retour d'erreur minishell ou bash

// ====>>>>
// exit 45fre
// exit
// bash: exit: 45fre: numeric argument required
// echo $? 2
// sort du bash 

// ====>>>>
// bash-5.1$ exit 
// exit
// echo $? 0
// sort du bash

// ====>>>>
// bash-5.1$ exit 255 255
// exit
// bash: exit: too many arguments

// sort du bash

// ====>>>>
// bash-5.1$ exit efef fefe 
// exit
// echo $?
// sort du bash

// ====>>>>
// bash-5.1$ exit [0 - 255]
// exit
// echo $? [0 - 255]

// ====>>>>
// bash-5.1$ exit +920368547758072
//

// si je fait exit sans arguments qui precede un 
//       commade qui a rate, je dois retourner se nombre
void	free_env_export(t_env *env, t_export *export)
{
	free_export(export);
	ft_free_env(env);
}

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

static int	size_nbrs(t_env *env, t_export *export, char *str)
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
		free_env_export(env, export);
		exit (2);
	}
	return (1);
}

int	ft_exit(t_env *env, t_export *export, char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		free_env_export(env, export);
		printf("exit\n");
		exit(0);
	}
	while (str[i] && size_nbrs(env, export, str[i]))
		i++;
	if (i > 1)
	{
		printf("exit\n");
		return (printf("minishell: exit: too many arguments\n"), 1);
	}
	printf("exit\n");
	free_env_export(env, export);
	ft_free(str);
	exit(ft_atoll(str[0]));
}
