/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:35:24 by scely             #+#    #+#             */
/*   Updated: 2024/05/06 14:52:39 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dst, const char *src)
{
	while (*src)
		*dst++ = *src++;
	*dst = '\0';
}

void	update_line(char *newline, int *to_copy, char *line, char *buf)
{
	if (newline != NULL)
	{
		*to_copy = newline - line + 1;
		ft_strcpy(buf, newline + 1);
	}
	else
	{
		*to_copy = ft_strlen(line);
		buf[0] = '\0';
	}
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	char		*newline;
	int			countread;
	int			to_copy;

	to_copy = 0;
	newline = NULL;
	line = ft_strdup(buf);
	countread = 1;
	while (!ft_strchr(line, '\n') && countread)
	{
		newline = ft_strchr(line, '\n');
		countread = read(fd, buf, BUFFER_SIZE);
		buf[countread] = '\0';
		line = ft_free_strjoin(line, buf);
	}
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	update_line(newline, &to_copy, line, buf);
	line[to_copy] = '\0';
	return (line);
}
