/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkaraka <akkaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 21:25:46 by akkaraka          #+#    #+#             */
/*   Updated: 2026/06/12 21:17:11 by akkaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_read_join(int fd, char **rest)
{
	char	*chunk;
	char	*temp;
	int		bytes_read;

	bytes_read = 0;
	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (-1);
	while (!ft_strchr(*rest, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(*rest, chunk);
		if (!temp)
			return (free(chunk), -1);
		free(*rest);
		*rest = temp;
		if (ft_strchr(chunk, '\n'))
			break ;
	}
	free(chunk);
	return (bytes_read);
}

char	*ft_get_line(char **rest)
{
	int	len;

	if (!*rest)
		return (NULL);
	len = 0;
	while ((*rest)[len] && (*rest)[len] != '\n')
		len++;
	if ((*rest)[len] == '\n')
		len++;
	return (ft_substr(*rest, 0, len));
}

char	*ft_get_rest(char **rest)
{
	int		i;
	char	*n_rest;
	char	*tmp;

	if (!*rest)
		return (NULL);
	i = 0;
	while ((*rest)[i] && (*rest)[i] != '\n')
		i++;
	if (!(*rest)[i])
		return (free(*rest), *rest = NULL, NULL);
	tmp = *rest;
	n_rest = ft_substr(tmp, i + 1, ft_strlen(tmp) - i - 1);
	free(tmp);
	if (!n_rest || !*n_rest)
		return (free(n_rest), *rest = NULL, NULL);
	return (*rest = n_rest, n_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_read_join(fd, &rest) == -1)
		return (free(rest), rest = NULL, NULL);
	line = ft_get_line(&rest);
	if (!line || !*line)
		return (free(line), free(rest), rest = NULL, NULL);
	ft_get_rest(&rest);
	return (line);
}
