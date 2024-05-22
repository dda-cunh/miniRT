/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:57:14 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/07 16:41:56 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*dup;

	s_len = ft_strlen(s);
	dup = (char *) ft_calloc(s_len + 1, sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s, s_len);
	dup[s_len] = '\0';
	return (dup);
}
