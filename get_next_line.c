/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkaraka <akkaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 21:25:46 by akkaraka          #+#    #+#             */
/*   Updated: 2026/05/26 17:49:20 by akkaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_join(int fd, char *rest)
{
	char	*chunk;
	int		bytes_read;
	char	*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);	
	while (1)
	{
		if (ft_strchr(rest, '\n'))
			break ;
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read == 0)
			break ;
		if (bytes_read < 0)
		{
			free(chunk);
			return (NULL);
		}
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(rest, chunk);
		free(rest);
		rest = temp;
	}
	free(chunk);
	return (rest);
}

char	*ft_get_line(char *rest)
{
	int	len;

	if (!rest || !*rest)
		return (NULL);
	len = 0;
	while (rest[len] && rest[len] != '\n')
		len++;
	if (rest[len] == '\n')
		len++;
	return (ft_substr(rest, 0, len));
}

char	*ft_get_rest(char *rest)
{
	int		i;
	char	*n_rest;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i] || ft_strlen(rest) == 0)
	{
		free(rest);
		return (NULL);
	}
	n_rest = ft_substr(rest, i + 1, ft_strlen(rest) - i - 1);
	free(rest);
	if (!n_rest || !*n_rest)
	{
		free(n_rest);
		return (NULL);
	}
	return (n_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = ft_read_join(fd, rest);
	if (!temp)
	{
		if (rest)
			free(rest);
		rest = NULL;
		return (NULL);
	}
	else
		rest = temp;
	line = ft_get_line(rest);
	rest = ft_get_rest(rest);
	if (!line)
	{
		if (rest)
			free(rest);
		return (NULL);
	}
	return (line);
}
