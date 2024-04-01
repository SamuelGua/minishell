/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:42:55 by scely             #+#    #+#             */
/*   Updated: 2023/11/16 13:01:32 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_split(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	if (s[0] != c && s[0] != '\0')
		nb_words++;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c) && s[i + 1] != '\0')
			nb_words++;
		i++;
	}
	return (nb_words);
}

static char	**ft_malloc(char const *s, char c, int i)
{
	char	**dest;
	int		k;
	int		j;

	j = 0;
	dest = malloc(sizeof(char *) * (i + 1));
	if (!dest)
		return (NULL);
	dest[i] = (char *) '\0';
	i = 0;
	while (s[i])
	{
		if (s[i] != c && s[i])
		{
			k = ft_strlen_split(&s[i], c);
			dest[j++] = malloc(sizeof(char) * k + 1);
			if (!dest)
				return (NULL);
			dest[j - 1][k] = '\0';
			i += k;
		}
		else
			i++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	int		k;
	int		j;

	if (s == NULL)
		return (NULL);
	new = ft_malloc(s, c, count_words(s, c));
	if (!new)
		return (NULL);
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		k = 0;
		while (s[i] != c && s[i])
		{
			new[j][k++] = s[i++];
			if (s[i] == c)
				j++;
		}
	}
	return (new);
}
