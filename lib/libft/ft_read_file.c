/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_all_lines.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:17:30 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/25 01:48:34 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*old_content;
	char	*full_content;
	char	*curr_content;
	int		r;

	full_content = NULL;
	ft_bzero(buffer, BUFFER_SIZE);
	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0)
	{
		curr_content = ft_strdup(buffer);
		if (!curr_content)
			break ;
		old_content = full_content;
		full_content = ft_strjoin(full_content, curr_content);
		free(curr_content);
		if (old_content)
			free(old_content);
		ft_bzero(buffer, BUFFER_SIZE);
		r = read(fd, buffer, BUFFER_SIZE);
	}
	return (full_content);
}
