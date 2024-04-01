/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:28:32 by scely             #+#    #+#             */
/*   Updated: 2023/11/14 12:02:11 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*e;

	i = 0;
	d = (unsigned char *)s1;
	e = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (d[i] != e[i])
			return (d[i] - e[i]);
		i++;
	}
	return (0);
}
