/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkaraka <akkaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 21:25:46 by akkaraka          #+#    #+#             */
/*   Updated: 2026/06/12 23:43:30 by akkaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		res = ft_strjoin(*line, "");
		free(*line);
		*line = NULL;
		rest[0] = '\0';
	}
	return (res);
}

char	*get_next_line(int fd)
{
	static char	rest[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (ft_read_join(fd, rest, &line) == -1)
		return (NULL);
	return (ft_get_line(&line, rest));
}
