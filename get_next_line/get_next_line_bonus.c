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

static	void	*clear_arr(char **arr)
{
	int	i;

	i = 0;
	while (i < OPEN_MAX)
	{
		if (arr[i])
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		i++;
	}
	return (NULL);
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
	if (!line)
		return (free(*depot), *depot = 0, NULL);
	new_depot = 0;
	if ((*depot)[i] == '\n')
		new_depot = ft_strdup((*depot) + i + 1);
	if ((*depot)[i] == '\n' && !new_depot)
		return (free(*depot), *depot = 0, free(line), line = 0, NULL);
	return (free(*depot), *depot = new_depot, line);
}

static ssize_t	ft_parse_data(int fd, char **depot)
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
			*depot = tmp;
			if (!*depot)
				return (free(buffer), -1);
		}
	}
	return (free(buffer), bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*depot[OPEN_MAX];
	ssize_t		bytes_read;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE < 1)
		return (clear_arr(depot));
	while (!depot[fd] || !ft_strchr(depot[fd], '\n'))
	{
		bytes_read = ft_parse_data(fd, &depot[fd]);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
			return (NULL);
	}
	return (ft_extract_line(&depot[fd]));
}
