/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:30:52 by gdosch            #+#    #+#             */
/*   Updated: 2024/11/29 11:30:54 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	i;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		((char *)arr)[i] = '\0';
		i++;
	}
	return (arr);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

static int	ft_build_line(char **line, char *buffer)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	tmp = ft_calloc(ft_strlen(*line) + i + (buffer[i] == '\n') + 1, 1);
	if (!tmp)
		return (free(*line), *line = 0, -1);
	if (*line)
		ft_memcpy(tmp, *line, ft_strlen(*line));
	ft_memcpy(tmp + ft_strlen(*line), buffer, i + (buffer[i] == '\n'));
	tmp[ft_strlen(*line) + i + (buffer[i] == '\n')] = '\0';
	free(*line);
	*line = tmp;
	if (!*line)
		return (free(tmp), tmp = 0, -1);
	if (buffer[i] == '\n')
		ft_memcpy(buffer, buffer + i + 1, ft_strlen(buffer) - i);
	else
		(buffer[0] = '\0');
	return (0);
}

static ssize_t	ft_parse_data(int fd, char *buffer, char **line)
{
	ssize_t	bytes_read;

	if (buffer[0] == '\0')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(*line), *line = 0, -1);
		if (bytes_read == 0)
			return (0);
		buffer[bytes_read] = '\0';
	}
	if (ft_build_line(line, buffer) < 0)
		return (-1);
	if (ft_strchr(*line, '\n'))
		return (0);
	return (1);
}

char	*get_next_line(int fd)
{
	static char	buffer[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			status;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= OPEN_MAX)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		status = ft_parse_data(fd, buffer[fd], &line);
		if (status == 0)
			break ;
		if (status == -1)
			return (NULL);
	}
	if (!*line)
		return (free(line), line = 0, NULL);
	return (line);
}
