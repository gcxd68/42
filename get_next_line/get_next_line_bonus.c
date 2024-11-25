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

static char	*ft_extract_line(char **storage)
{
	char	*line;
	char	*new_storage;
	size_t	i;

	if (!*storage || (*storage)[0] == '\0')
		return (free(*storage), *storage = NULL, NULL);
	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	new_storage = NULL;
	if ((*storage)[i] == '\n')
	{
		line = ft_substr(*storage, 0, i + 1);
		new_storage = ft_strdup((*storage) + i + 1);
	}
	else
		line = ft_substr(*storage, 0, i);
	if (!line || (!new_storage && (*storage)[i] == '\n'))
		return (free(*storage), *storage = NULL, NULL);
	return (free(*storage), *storage = new_storage, line);
}

static ssize_t	ft_append_from_fd(int fd, char **storage, char **buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(*buffer), free(*storage), *storage = NULL, -1);
	if (bytes_read > 0)
	{
		(*buffer)[bytes_read] = '\0';
		if (!*storage)
			*storage = ft_strdup(*buffer);
		else
		{
			tmp = ft_strjoin(*storage, *buffer);
			if (!tmp)
				return (free(*buffer), free(*storage), *storage = NULL, -1);
			free(*storage);
			*storage = tmp;
		}
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!storage[fd] || !ft_strchr(storage[fd], '\n'))
	{
		bytes_read = ft_append_from_fd(fd, &storage[fd], &buffer);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	return (free(buffer), ft_extract_line(&storage[fd]));
}
