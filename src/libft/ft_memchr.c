/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:56:40 by scely             #+#    #+#             */
/*   Updated: 2023/11/14 09:45:48 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	c2;

	c2 = c;
	while (n > 0)
	{
		if (c2 == *(unsigned char *)s)
			return ((unsigned char *)s);
		s++;
		n--;
	}
	return (0);
}
