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

static char	*ft_free_mem(char **storage)
{
	if (storage && *storage)
	{
		free (storage);
		storage = NULL;
	}
	return (NULL);
}

static char	*ft_extract_line(char **storage)
{
	char	*line;
	char	*new_storage;
	size_t	i;

	if (!*storage || **storage == '\0')
		return (ft_free_mem(storage));
	i = 0;
	while ((*storage)[i] && (*storage)[i] != '\n')
		i++;
	new_storage = NULL;
	if ((*storage)[i] == '\n')
	{
		line = ft_substr(*storage, 0, i + 1);
		new_storage = ft_strdup((*storage) + i + 1);
		if (!new_storage)
			return (NULL);
	}
	else
		line = ft_substr(*storage, 0, i);
	if (!line)
		return (NULL);
	free(*storage);
	*storage = new_storage;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!storage || !ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (ft_free_mem(&storage));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!storage)
			storage = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(storage, buffer);
			free(storage);
			storage = tmp;
		}
	}
	return (ft_extract_line(&storage));
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Erreur d'ouverture du fichier texte");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
