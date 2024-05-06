/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:38 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 19:06:32 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// => les deux commandes s'expandent
// echo $PWD
// echo "$PWD"

// => ca ne s'expande pas 
// echo '$PWD'

// gerer les quotes

static void	print_echo(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{	
		ft_putstr_fd(str[i], 1);
		if (str[i + 1] && str[i + 1][0] != '\0')
			ft_putstr_fd(" ", 1);
		i++;
	}
}

char	**check_flag(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[++i])
	{
		j = 0;
		if (str[i][0] == '-' && str[i][1])
			j++;
		else
			return (&str[i]);
		while (str[i][j] && str[i][j] == 'n')
			j++;
		if (str[i][j] != '\0')
			return (&str[i]);
	}
	return (&str[i]);
}

int	dash_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '-' && !str[1])
		return (0);
	if (str[0] != '-')
		return (0);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **str)
{
	int	i;
	char	**test;

	i = 0;
	if (str[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	test = check_flag(str);
	if (dash_n(str[1]))
	{
		print_echo(test);
		return (0);
	}
	print_echo(test);
	ft_putstr_fd("\n", 1);
	return (0);
}
