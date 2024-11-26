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

static char	*ft_extract_line(char **depot)
{
	char	*line;
	char	*new_depot;
	size_t	i;

	if (!*depot || (*depot)[0] == '\0')
		return (free(*depot), *depot = NULL, NULL);
	i = 0;
	while ((*depot)[i] && (*depot)[i] != '\n')
		i++;
	new_depot = NULL;
	if ((*depot)[i] == '\n')
	{
		line = ft_substr(*depot, 0, i + 1);
		new_depot = ft_strdup((*depot) + i + 1);
	}
	else
		line = ft_substr(*depot, 0, i);
	if (!line || (!new_depot && (*depot)[i] == '\n'))
		return (free(*depot), *depot = NULL, NULL);
	return (free(*depot), *depot = new_depot, line);
}

static ssize_t	ft_read_from_fd(int fd, char **depot, char **buffer)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(*buffer), free(*depot), *depot = NULL, -1);
	if (bytes_read > 0)
	{
		(*buffer)[bytes_read] = '\0';
		if (!*depot)
			*depot = ft_strdup(*buffer);
		else
		{
			tmp = ft_strjoin(*depot, *buffer);
			if (!tmp)
				return (free(*buffer), free(*depot), *depot = NULL, -1);
			free(*depot);
			*depot = tmp;
		}
	}
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*depot = NULL;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!depot || !ft_strchr(depot, '\n'))
	{
		bytes_read = ft_read_from_fd(fd, &depot, &buffer);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	return (free(buffer), ft_extract_line(&depot));
}
