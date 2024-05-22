/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:22:34 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/07 02:49:34 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned char	n_digs(long n)
{
	if (n == 0)
		return (0);
	if (n < 0)
		return (2 + n_digs(-n / 10));
	return (1 + n_digs(n / 10));
}

char	*ft_itoa(int n)
{
	unsigned char	len;
	unsigned char	neg;
	char			*a;

	if (n == 0)
		return (ft_strdup("0"));
	len = n_digs(n);
	neg = 0;
	if (n < 0)
		neg = 1;
	a = (char *) ft_calloc(len + 1, sizeof(char));
	if (!a)
		return (NULL);
	while (n)
	{
		a[--len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (neg)
		a[--len] = '-';
	return (a);
}
