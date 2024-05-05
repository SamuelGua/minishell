/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:59 by scely             #+#    #+#             */
/*   Updated: 2024/05/04 04:44:21 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PWD_ERROR  "pwd: error retrieving current directory: " 
#define PWD_ERROR2 "getcwd: cannot access parent directories"

int	ft_pwd(void)
{
	char	*path_name;

	path_name = getcwd(NULL, 0);
	if (!path_name)
	{
		perror(PWD_ERROR PWD_ERROR2);
		return (1);
	}
	printf("%s\n", path_name);
	return (0);
}
