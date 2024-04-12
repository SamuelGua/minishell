/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:59 by scely             #+#    #+#             */
/*   Updated: 2024/04/12 17:53:17 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PWD_ERROR  "pwd: error retrieving current directory: " 
#define PWD_ERROR2 "getcwd: cannot access parent directories"

void	ft_pwd(void)
{
	char	*path_name;

	path_name = getcwd(NULL, 0);
	if (!path_name)
	{
		perror(PWD_ERROR PWD_ERROR2);
		return ;
	}
	printf("%s\n", path_name);
}
