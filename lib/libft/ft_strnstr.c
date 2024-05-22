/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 22:48:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/07 17:48:22 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_l;
	size_t	big_i;
	size_t	same;

	if (!big)
		return (NULL);
	if (!*little)
		return ((char *)big);
	little_l = ft_strlen(little);
	big_i = 0;
	while (big_i < len && big[big_i])
	{
		same = 0;
		while (big_i + same < len && same < little_l
			&& big[big_i + same] == little[same])
			same++;
		if (same == little_l)
			return ((char *)(big + big_i));
		big_i += same;
		if (same == 0)
			big_i++;
	}
	return (NULL);
}
