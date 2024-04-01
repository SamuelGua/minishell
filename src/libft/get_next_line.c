/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scely <scely@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 08:49:47 by scely             #+#    #+#             */
/*   Updated: 2024/01/10 11:17:04 by scely            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

void	read_line(int fd, char **temp, int *lues)
{
	char	*buffer;

	if (!*temp)
		*temp = ft_calloc(1, 1);
	while (*lues >= 1 && ft_strchr(*temp, '\n') == 0)
	{
		buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		*lues = read(fd, buffer, BUFFER_SIZE);
		if (((*temp == NULL) && *lues == 0) || *lues == -1)
		{
			free(buffer);
			return ;
		}
		buffer[*lues] = '\0';
		*temp = ft_strjoin_free(*temp, buffer);
		free(buffer);
	}
}

void	extract_line(char *temp, char **line)
{
	int		len;

	len = 0;
	if (temp == NULL)
		return ;
	while (temp[len] && temp[len] != '\n')
		len++;
	*line = ft_substr(temp, 0, len + 1);
	if (*line == NULL)
		return ;
}

char	*clean_temp(char *temp)
{
	int		i;
	int		j;
	char	*c;

	i = 0;
	while (temp[i] != '\n' && temp[i])
		i++;
	if (!temp[i])
	{
		free(temp);
		return (NULL);
	}
	j = (int)ft_strlen(&temp[i]);
	c = ft_substr(temp, i + 1, j);
	if (!c)
		return (NULL);
	free(temp);
	return (c);
}

char	*get_next_line(int fd)
{
	static char		*temp[1024];
	char			*line;
	int				lues;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	lues = 1;
	read_line(fd, &temp[fd], &lues);
	if (temp[fd] == NULL)
		return (NULL);
	extract_line(temp[fd], &line);
	if (line == NULL)
		return (NULL);
	temp[fd] = clean_temp(temp[fd]);
	if (line[0] == '\0')
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	return (line);
}
