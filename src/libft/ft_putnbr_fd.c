/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:06:04 by scely             #+#    #+#             */
/*   Updated: 2023/11/14 12:02:28 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	a;
	int	b;

	a = n % 10;
	b = n / 10;
	if (b)
		ft_putnbr_fd(b, fd);
	if (n < 0)
	{
		if (!b)
			ft_putchar_fd('-', fd);
		a = -a;
	}
	ft_putchar_fd(a + '0', fd);
}
