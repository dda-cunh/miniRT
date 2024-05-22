/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:26:35 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/17 17:04:47 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	strlen(const char *str)
{
	size_t	l;

	l = 0;
	if (str)
		while (str[l])
			l++;
	return (l);
}

static void	*memset(void *s, int c, size_t n)
{
	unsigned char	*bytes;

	bytes = (unsigned char *)s;
	while (n--)
		*bytes++ = (unsigned char)c;
	return (s);
}

static void	*memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src_bytes;
	unsigned char	*desints;
	size_t			i;

	if (!src || !dest)
		return (NULL);
	src_bytes = (unsigned char *)src;
	desints = (unsigned char *)dest;
	if (desints >= src_bytes && desints <= src_bytes + n)
	{
		if (dest)
			while (n--)
				desints[n] = src_bytes[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			desints[i] = src_bytes[i];
			i++;
		}
	}
	return (dest);
}

static char	*alloc_concat(char *line, char *buff)
{
	size_t	concat_l;
	size_t	concat_i;
	size_t	buff_i;
	char	*concat;

	concat_l = strlen(line);
	buff_i = 0;
	while (buff_i < BUFFER_SIZE && !buff[buff_i])
		buff_i++;
	while (buff_i < BUFFER_SIZE)
	{
		concat_l++;
		if (buff[buff_i] == '\n')
			break ;
		buff_i++;
	}
	concat = malloc((concat_l + 1) * sizeof(char));
	concat_i = 0;
	while (concat_i < concat_l + 1)
	{
		concat[concat_i] = '\0';
		concat_i++;
	}
	return (concat);
}

char	*line_join(char *line, char *buff)
{
	long	buff_empty_i;
	long	breakline_i;
	long	concat_i;
	char	*concat;

	concat = alloc_concat(line, buff);
	if (!concat)
		return (NULL);
	concat_i = strlen(line);
	memmove(concat, line, concat_i);
	if (line)
		free(line);
	buff_empty_i = 0;
	while (buff_empty_i < BUFFER_SIZE && !buff[buff_empty_i])
		buff_empty_i++;
	breakline_i = buff_empty_i;
	while (breakline_i < BUFFER_SIZE)
		if (buff[breakline_i++] == '\n')
			break ;
	memmove(concat + concat_i, buff + buff_empty_i, breakline_i - buff_empty_i);
	memset(buff + buff_empty_i, 0, breakline_i - buff_empty_i);
	return (concat);
}
