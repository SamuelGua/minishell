/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buils_cmd_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:56:51 by scely             #+#    #+#             */
/*   Updated: 2024/05/11 11:57:34 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmds_size(t_token *tmp, t_token *end)
{
	int	i;

	i = 0;
	while (tmp != end)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	set_nbs(t_token *tmp, t_file *file, t_build_cmd *utl)
{
	if (tmp->token == HERE_DOC)
	{
		file->n_heredoc = utl->nb_here_doc;
		utl->nb_here_doc++;
	}
}
