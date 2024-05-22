/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_tail.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:03:26 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/07 16:55:42 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_tail(const char *s, size_t tail)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if (tail > s_len)
		return (NULL);
	return (ft_strdup(s + (s_len - tail)));
}
