/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:39:33 by scely             #+#    #+#             */
/*   Updated: 2023/11/14 11:44:59 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdio.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*dst;
	char	*s;
	size_t	i;

	i = 0;
	dst = (char *)dest;
	s = (char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i != n)
	{
		dst[i] = s[i];
		i++;
	}
	return (dest);
}
