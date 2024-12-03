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

static int	ft_build_line(char **line, char *buffer)
{
	char	*tmp;
	size_t	line_len;
	size_t	chunk_len;
	size_t	i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line_len = ft_strlen(*line);
	chunk_len = i + (buffer[i] == '\n');
	tmp = malloc(line_len + chunk_len + 1);
	if (!tmp)
		return (free(*line), *line = 0, -1);
	if (*line)
		ft_memcpy(tmp, *line, line_len);
	ft_memcpy(tmp + line_len, buffer, chunk_len);
	tmp[line_len + chunk_len] = '\0';
	free(*line);
	*line = tmp;
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
