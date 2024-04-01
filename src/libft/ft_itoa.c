/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iota.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:46:39 by scely             #+#    #+#             */
/*   Updated: 2023/11/13 19:28:40 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nulen(int o)
{
	int	i;

	i = 0;
	if (o <= 0)
		i++;
	while (o != 0)
	{
		o /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*new;
	int			i;
	long int	n2;

	n2 = n;
	i = ft_nulen(n);
	new = malloc(sizeof(char) * i + 1);
	if (!new)
		return (0);
	if (n < 0)
	{
		n2 *= -1;
		new[0] = '-';
	}
	new[i] = '\0';
	if (n2 == 0)
		new[0] = '0';
	while (n2 > 0)
	{
		i--;
		new[i] = n2 % 10 + '0';
		n2 /= 10;
	}
	return (new);
}
