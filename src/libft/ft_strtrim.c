/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:29:10 by scely             #+#    #+#             */
/*   Updated: 2023/11/16 12:58:56 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_start(char const *s1, char const *set)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (s1[i])
	{
		if (set[k] == '\0')
			return (i);
		else if (s1[i] == set[k])
		{
			i++;
			k = 0;
		}
		else
			k++;
	}
	return (i);
}

static int	find_end(char const *s1, char const *set)
{
	int	i;
	int	k;
	int	l;

	l = 0;
	k = 0;
	i = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (set[k] == '\0')
			return (l);
		else if (s1[i] == set[k])
		{
			i--;
			l++;
			k = 0;
		}
		else
			k++;
	}
	return (l);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		start;
	int		end;
	int		i;
	int		k;

	if (s1 == NULL)
		return (NULL);
	start = find_start(s1, set);
	end = find_end(s1, set);
	i = ft_strlen(s1);
	k = 0;
	if (i < (start + end))
	{
		start = 0;
		end = 0;
		i = 0;
	}
	new = malloc(sizeof(char) * (i - (start + end)) + 1);
	if (!new)
		return (NULL);
	while (start < (i - end))
		new[k++] = s1[start++];
	new[k] = '\0';
	return (new);
}
