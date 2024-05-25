/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_all_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 01:52:33 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/25 01:57:28 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_get_all_lines(int fd)
{
	char	*file_contents;
	char	**lines;

	file_contents = ft_read_file(fd);
	if (!file_contents)
		return (NULL);
	lines = ft_split(file_contents, '\n');
	free(file_contents);
	return (lines);
}
