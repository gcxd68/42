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
		return (free(*depot), *depot = 0, NULL);
	i = 0;
	while ((*depot)[i] && (*depot)[i] != '\n')
		i++;
	line = ft_substr(*depot, 0, i + ((*depot)[i] == '\n'));
	new_depot = 0;
	if ((*depot)[i] == '\n')
		new_depot = ft_strdup((*depot) + i + 1);
	if (!line || (!new_depot && (*depot)[i] == '\n'))
		return (free(*depot), *depot = 0, NULL);
	return (free(*depot), *depot = new_depot, line);
}

static ssize_t	ft_read_from_fd(int fd, char **depot)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(*depot), *depot = 0, -1);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(buffer), free(*depot), *depot = 0, -1);
	if (bytes_read > 0)
	{
		(buffer)[bytes_read] = '\0';
		if (!*depot)
			*depot = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(*depot, buffer);
			free(*depot);
			if (!tmp)
				return (free(buffer), *depot = 0, -1);
			*depot = tmp;
		}
	}
	return (free(buffer), bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*depot = 0;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (free(depot), depot = 0, NULL);
	while (!depot || !ft_strchr(depot, '\n'))
	{
		bytes_read = ft_read_from_fd(fd, &depot);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	return (ft_extract_line(&depot));
}
