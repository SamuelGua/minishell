/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 09:33:59 by scely             #+#    #+#             */
/*   Updated: 2024/04/08 09:34:19 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*path_name;

	path_name = getcwd(NULL, 0);
	if (!path_name)
	{
		printf("Error malloc\n");
		return ;
	}
	printf("%s\n", path_name);
}
