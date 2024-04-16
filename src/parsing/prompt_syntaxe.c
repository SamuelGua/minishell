/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_syntaxe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:30:39 by scely             #+#    #+#             */
/*   Updated: 2024/04/12 09:38:45 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted(int quoted, char c)
{
	if (quoted == 0 && c == '\'')
		return (S_QUOTE);
	else if (quoted == 0 && c == '\"')
		return (D_QUOTE);
	else if (quoted == S_QUOTE && c == '\'')
		return (NO_QUOTE);
	else if (quoted == D_QUOTE && c == '\"')
		return (NO_QUOTE);
	return (quoted);
}
