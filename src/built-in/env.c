/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 12:45:36 by scely             #+#    #+#             */
/*   Updated: 2024/04/08 16:32:06 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//condition au cas si on lui donne un arguments, si cela est un fichier ou un elements inconnu
// si l'arguments est un executable il execute
// dans la correction il dise de gere env sans arguments et sans option. Dans le cas ou il y en un je print quand meme mon env
void	ft_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->cle, env->params);
		env = env->next;
	}
}
