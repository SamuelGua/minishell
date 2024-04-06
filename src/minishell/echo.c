/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 12:37:38 by scely             #+#    #+#             */
/*   Updated: 2024/04/06 14:26:13 by scely            ###   ########.fr       */
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
static int is_env(t_env *env, char *str)
{
	int i;

	i = 0;
	while (env && ft_strncmp(env->cle, str+1, ft_strlen(str) - 1) != 0)
		env = env->next;
	if (env)
	{
		printf("%s",env->params);
		return (1);
	}
	else
		return (0);
	
}
static void print_echo(t_env *env, char **str)
{
	int	i;

	i = -1;
	while(str[++i])
	{	
		if (str[i][0] == '$' && ft_strlen(str[i]) > 1)
		{
			if (i != 0 && is_env(env, str[i]))
				printf(" ");
		}
		else
		{
			if (i !=  0)
				printf(" ");
			printf("%s", str[i]);
		}
	}
}

void	ft_echo(t_env *env,char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(str[i], "-n", 2) == 0)
	{
		print_echo(env, &str[i + 1]);
		return ;
	}
	print_echo(env, str);
	printf("\n");
}
