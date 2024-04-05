/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:48:46 by scely             #+#    #+#             */
/*   Updated: 2024/04/05 19:16:35 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// La derniere variables est _ on peut l'unset mais cela sera juste recree derriere
// soit je mets une limite pour que lon ne puisse pas l'unset, soit je peut l'unset mais qu'apres je le mets a jours apres chaque execution
// envoyer un tableau avec tout les varaibles a unset
void	ft_unset(t_env *env, char **str)
{
// mettre env en ** pour ne pas prendre le pointeurs lorsque l'on modifie la tete
	t_env	*tmp;
	t_env	*head;
	int		str_len;
	int		i;

	i = 0;
	head = env;
	if (str == NULL)
		return ;
	while (str[i])
	{
		str_len = ft_strlen(str[i]);
		env = head;
		while (env)
		{
			head = env->next;
			if (ft_strncmp(str[i], env->cle, str_len) == 0)
			{
				printf("%s ok\n", env->cle);	
				if (ft_strncmp(env->cle, head->cle, ft_strlen(env->cle)) == 0)
					head = env->next;
				tmp->next = env->next;
				(free(env->cle), free(env->params), free(env));
				break;
			}
			tmp = env;
			env = env->next;
		}
		i++;
		printf("tmp = %s\n", env->cle);
	}
}
