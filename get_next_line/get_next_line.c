/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdosch <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:15:45 by gdosch            #+#    #+#             */
/*   Updated: 2024/11/18 15:15:47 by gdosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	arr = malloc(nmemb * size);
	if (!arr)
		return (NULL);
	ft_bzero(arr, nmemb * size);
	return (arr);
}

static int	ft_extract_line(char **line, char *buffer)
{
	char	*tmp;
	char	*substr;
	size_t	i;

//	if (!buffer || buffer[0] == '\0')
//		return (free(*line), *line = 0, -1);
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

static ssize_t	ft_read_from_fd(int fd, char *buffer, char **line)
{
	ssize_t		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(*line), *line = 0, -1);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = ft_read_from_fd(fd, buffer, &line);
			if (bytes_read == 0)
				break ;
			if (bytes_read == -1)
				return (NULL);
		}
		if (ft_extract_line(&line, buffer) < 0)
			return (NULL);
	}
	if (!*line)
		return (free(line), line = 0, NULL);
	return (line);
}
