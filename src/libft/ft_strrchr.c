/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:59:49 by scely             #+#    #+#             */
/*   Updated: 2023/11/13 19:29:47 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	int			len;
	char		c2;
	const char	*d;

	i = 0;
	c2 = c;
	len = 0;
	while (s[i])
	{
		if (s[i] == c2)
		{
			d = &s[i];
			len++;
		}
		i++;
	}
	if (c == 0)
		return ((char *)&s[i]);
	else if (len == 0)
		return (0);
	return ((char *)d);
}
