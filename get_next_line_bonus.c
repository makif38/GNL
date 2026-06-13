/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkaraka <akkaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:58:37 by akkaraka          #+#    #+#             */
/*   Updated: 2026/06/13 21:31:03 by akkaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_read_join(int fd, char *rest, char **line)
{
	char	chunk[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*tmp;

	while (!ft_strchr(rest, '\n'))
	{
		if (*rest)
			return (tmp = ft_strjoin(*line, rest), free(*line),
				*line = tmp, rest[0] = '\0', ft_read_join(fd, rest, line));
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(*line), *line = NULL, rest[0] = '\0', -1);
		if (bytes_read == 0)
			return (0);
		chunk[bytes_read] = '\0';
		if (ft_strchr(chunk, '\n'))
			return (ft_strlcat(rest, chunk, BUFFER_SIZE + 1), 1);
		tmp = ft_strjoin(*line, chunk);
		free(*line);
		*line = tmp;
	}
	return (1);
}

char	*ft_get_line(char **line, char *rest)
{
	char	*nline_pos;
	char	*res;
	char	*tmp;

	nline_pos = ft_strchr(rest, '\n');
	if (!nline_pos && (!*line || !**line))
		return (NULL);
	if (nline_pos)
	{
		*nline_pos = '\0';
		tmp = ft_strjoin(*line, rest);
		free(*line);
		*line = NULL;
		res = ft_strjoin(tmp, "\n");
		free(tmp);
		ft_memmove(rest, nline_pos + 1, ft_strlen(nline_pos + 1) + 1);
	}
	else
	{
		res = ft_strjoin(*line, rest);
		free(*line);
		*line = NULL;
		rest[0] = '\0';
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	rest[MAX_FD][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (ft_read_join(fd, rest[fd], &line) == -1)
		return (NULL);
	return (ft_get_line(&line, rest[fd]));
}
