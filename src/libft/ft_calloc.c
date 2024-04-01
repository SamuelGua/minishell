/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:34:34 by scely             #+#    #+#             */
/*   Updated: 2023/11/13 19:28:36 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*d;
	size_t	i;
	size_t	j;

	if (count == 0 || size == 0)
		j = 1;
	else if (count > 65535 || size > 65535 || count * size > 65535)
		return (NULL);
	else
		j = count * size;
	i = 0;
	d = malloc(j);
	if (d == 0)
		return (0);
	while (j > 0)
	{
		d[i] = '\0';
		j--;
		i++;
	}
	return ((void *)d);
}
