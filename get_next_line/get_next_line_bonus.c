/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 09:34:53 by gdosch            #+#    #+#             */
/*   Updated: 2024/11/25 09:34:54 by gdosch           ###   ########.fr       */
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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d < s || d >= s + n)
	{
		while (n--)
			*d++ = *s++;
	}
	else
	{
		d = d + n - 1;
		s = s + n - 1;
		while (n--)
			*d-- = *s--;
	}
	return (dest);
}

static int	ft_extract_line(char **line, char *buffer)
{
	char	*tmp;
	char	*substr;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	substr = ft_substr(buffer, 0, i + (buffer[i] == '\n'));
	if (!substr)
		return (free(*line), *line = 0, -1);
	tmp = ft_strjoin(*line, substr);
	free(substr);
	if (!tmp)
		return (free(*line), *line = 0, -1);
	free(*line);
	*line = tmp;
	if (buffer[i] == '\n')
		ft_memmove(buffer, buffer + i + 1, ft_strlen(buffer) - i);
	else
		(buffer[0] = '\0');
	return (0);
}

static int	ft_parse_buffer(int fd, char *buffer, char **line)
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
	if (ft_extract_line(line, buffer) < 0)
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

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		status = ft_parse_buffer(fd, buffer[fd], &line);
		if (status == 0)
			break ;
		if (status == -1)
			return (NULL);
	}
	if (!*line)
		return (free(line), line = 0, NULL);
	return (line);
}
