/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 18:38:40 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/17 17:04:47 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *restrict dest, const void *restrict src, size_t n)
{
	unsigned char	*src_bytes;
	unsigned char	*desints;

	src_bytes = (unsigned char *)src;
	desints = (unsigned char *)dest;
	if (desints >= src_bytes && desints <= src_bytes + n)
		return (ft_memmove(dest, src, n));
	while (n--)
		*desints++ = *src_bytes++;
	return (dest);
}
