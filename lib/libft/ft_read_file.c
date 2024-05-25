/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 00:17:30 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/25 15:33:01 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_file(int fd)
{
	char	buffer[BUFFER_SIZE];
	char	*full_content;
	char	*old_content;
	int		r;

	full_content = NULL;
	ft_bzero(buffer, BUFFER_SIZE);
	r = read(fd, buffer, BUFFER_SIZE);
	while (r > 0)
	{
		old_content = full_content;
		full_content = ft_strjoin(full_content, buffer);
		if (old_content)
			free(old_content);
		ft_bzero(buffer, BUFFER_SIZE);
		r = read(fd, buffer, BUFFER_SIZE);
	}
	return (full_content);
}
