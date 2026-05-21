/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkaraka <akkaraka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 21:25:46 by akkaraka          #+#    #+#             */
/*   Updated: 2026/05/21 21:49:39 by akkaraka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_join(int fd, char *rest)
{
	char	*chunk;
	int		bytes_read;

	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);
	bytes_read = 1;// 1 damit schleife loslaufen kann------------------------------------------------------------------
	while (bytes_read > 0 && !ft_strchr(rest, '\n'))// solange wir lesen konnen und kein \n in rest ist -> weiterlesen
	{//----------------------------------------------------------------------------------------------------------------
		bytes_read = read(fd, chunk, BUFFER_SIZE);// frische Daten aus der Datei in Chunk lesen
		if (bytes_read == -1)// lesefehler -> chunk und rest freen
		{
			free(chunk);
			return (NULL);
		}
		chunk[bytes_read] = '\0';//-------------------------------------------------
		(void)ft_strlcpy(chunk, rest, ft_strlen(rest));// alten rest und neuen chunk zusammenkleben
	}
	return (chunk);
}

char	*ft_get_line(char *chunk)
{
	int	len;

	if (!chunk || !*chunk)
		return (NULL);
	len = 0;
	while (chunk[len] && chunk[len] != '\n')//zaehlen wie viele zeichen bis \n -> \n gefunden oder str ende
		len++;//--------------------------------------------------------------
	if (chunk[len] == '\n')//'\n' gefunden -> um 1 erhohen um '\n' mitzunehmen
		len++;//--------------------------------------------------------------
	return (ft_substr(chunk, 0, len));//schneide von posi 0 bis len raus -> fertige line
}

char	*ft_get_rest(char *rest)
{
	int		i;
	char	*n_rest;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	n_rest = ft_substr(rest, i + 1, ft_strlen(rest) - i - 1);//alles nach \n rausschneiden -> i + 1 (startet nach \n)-> strlen i - 1 (lange von rest)
	free(rest);
	return (n_rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;// bleibt zwischen 2 Aufrufen erhalten, speichert was nach dem \n ubrig bleibt
	char		*line;//----------------------------------------------------------------------------

	if (fd < 0 || BUFFER_SIZE <= 0)// ungultiger fd oder BUFFER_SIZE
		return (NULL);//-----------------------------------------------------------
	rest = ft_read_join(fd, rest);// liest solange bi \n in rest oder Datei zu Ende
	if (!rest)// Lesefehler oder Datei leer-----------------------------------------
		return (NULL);
	line = ft_get_line(rest);// schneidet Line bis \n-----------------------------
	rest = ft_get_rest(rest);//alles nach dem \n bleibt im rest fur nachste Aufruf
	return (line);//------------------------------------------------------------------
}
