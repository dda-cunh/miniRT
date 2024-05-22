/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:48:43 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/17 17:04:47 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_bytes;
	unsigned char	*desints;

	i = -1;
	src_bytes = (unsigned char *)src;
	desints = (unsigned char *)dest;
	if (desints >= src_bytes && desints <= src_bytes + n)
	{
		if (dest)
			while (n--)
				desints[n] = src_bytes[n];
	}
	else
		while (++i < n)
			desints[i] = src_bytes[i];
	return (dest);
}
