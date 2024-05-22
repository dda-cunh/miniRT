/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:26:03 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/28 15:55:02 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_bool	buff_has_residual(char *buffer)
{
	int	i;

	i = -1;
	while (++i < BUFFER_SIZE)
		if (buffer[i])
			return (TRUE);
	return (FALSE);
}

static t_bool	str_has_c(const char *str, char c)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			if (str[i] == c)
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}

static char	*seek_line(char *buffer, char *line, long bytes_read, int fd)
{
	if (str_has_c(line, '\n'))
		return (line);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		if (line)
			free(line);
		return (NULL);
	}
	if (bytes_read == 0)
		return (line);
	line = line_join(line, buffer);
	if (!line)
		return (NULL);
	return (seek_line(buffer, line, bytes_read, fd));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE] = {0};
	char		*line;

	line = NULL;
	if (buff_has_residual(buffer))
		line = line_join(line, buffer);
	line = seek_line(buffer, line, 1, fd);
	return (line);
}
