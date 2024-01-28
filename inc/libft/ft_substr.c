/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:09:39 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/28 16:35:44 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	char	*sub_str;

	s_len = ft_strlen(s);
	if (start > s_len || len == 0)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	sub_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!sub_str)
		return (NULL);
	i = -1;
	while (++i < len)
		sub_str[i] = s[i + start];
	return (sub_str);
}
