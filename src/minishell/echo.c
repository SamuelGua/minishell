/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:38 by scely             #+#    #+#             */
/*   Updated: 2024/04/06 14:45:19 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//echo "maman je t'aime"
//echo "maman "je" t'aime"
//echo 'maman 'je' t'aime'
// = maman je taime

//echo "maman 'je' t'aime"
// = maman 'je' taime

//echo $PATH => /usr/bin...
//echo $path => 
static void print_echo(char **str)
{
	int	i;

	i = -1;
	while(str[++i])
	{	
			printf("%s", str[i]);
			if (str[i + 1])
				printf(" ");
	}
}

void	ft_echo(t_env *env, char **str)
{
	(void)env;
	int	i;

	i = 0;
	if (str == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(str[i], "-n", 2) == 0)
	{
		print_echo(&str[i + 1]);
		return ;
	}
	print_echo(str);
	printf("\n");
}
