/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkaraka <akkaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 21:25:46 by akkaraka          #+#    #+#             */
/*   Updated: 2026/05/28 20:36:36 by akkaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_read_join(int fd, char **rest)
{
	char	*chunk;
	int		bytes_read;
	char	*temp;

	bytes_read = 0;
	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (-1);
	while (1)
	{
		if (ft_strchr(*rest, '\n'))
			break ;
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read == -1)
			return (free(chunk), -1);
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(*rest, chunk);
		free(*rest);
		*rest = temp;
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

	i = 0;
	if (!*rest)
		return (NULL);
	while ((*rest)[i] && (*rest)[i] != '\n')
		i++;
	n_rest = ft_substr(*rest, i + 1, ft_strlen(*rest) - i - 1);
	if (!n_rest)
		return (NULL);
	if (n_rest)
	{
		free(*rest);
		if (n_rest[0] != '\0')
			*rest = n_rest;
		else
		{
			free(n_rest);
			*rest = NULL;
		}
	}
	return (n_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*n_rest;
	int			error;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	error = ft_read_join(fd, &rest);
	if (error == -1)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	line = ft_get_line(&rest);
	n_rest = ft_get_rest(&rest);
	if (!n_rest)
		return (NULL);
	if (!line)
		return (free(line), NULL);
	return (line);
}
