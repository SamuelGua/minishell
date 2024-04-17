/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:38 by scely             #+#    #+#             */
/*   Updated: 2024/04/17 16:15:13 by scely            ###   ########.fr       */
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

	i = -1;
	while (str[++i])
	{	
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
}

char	**check_flag(char **str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = 0;
		if (str[i][0] == '-')
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
	if (str[0] != '-')
		return (0);
	while (str[i] == 'n' && str[i])
		i++;
	if (str[i] != '\0')
		return (0);
	return (1);
}

void	ft_echo(char **str, t_env *env)
{
	char	**test;
	int		i;
	(void)env;

	i = 0;
	if (str == NULL)
	{
		printf("\n");
		return ;
	}
	//check ""
	while (str[i])
	{
		str[i] = expansion(str[i], env);
		i++;
	}
	test = check_flag(str);
	if (dash_n(str[0]))
	{
		print_echo(test);
		ft_free(str);
		return ;
	}
	print_echo(test);
	printf("\n");
	ft_free(str);
}
