/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:05:30 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/07 16:57:24 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_strings(char const *s, char c)
{
	int	start;
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[start])
			n++;
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	char	**sep;
	int		start;
	int		i;
	int		j;

	sep = (char **) ft_calloc((n_strings(s, c) + 1), sizeof(char *));
	if (!sep)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (s[start])
			sep[j++] = ft_substr(s, start, i - start);
	}
	return (sep);
}
