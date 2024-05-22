/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 18:03:53 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/19 12:10:38 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size)
{
	unsigned char	*bytes;

	if (new_size <= prev_size)
		return (ptr);
	bytes = malloc(new_size);
	if (!ptr)
		return (bytes);
	if (!bytes)
	{
		free(ptr);
		return (NULL);
	}
	ft_memmove(bytes, ptr, prev_size);
	free(ptr);
	return (bytes);
}
