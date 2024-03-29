/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 19:13:22 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/29 19:18:11 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ndigs(long l)
{
	size_t	n;

	if (l == 0)
		return (1);
	n = 0;
	while (l != 0)
	{
		l /= 10;
		n++;
	}
	return (n);
}

static long	_atol(const char *nptr)
{
	long	sum;
	char	pol;

	pol = 1;
	sum = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*nptr++ == '-')
			pol = -1;
	while (ft_isdigit(*nptr))
		sum = sum * 10 + (*nptr++ - '0');
	return (pol * sum);
}

double	ft_atof(const char *nptr)
{
	double	decimal;
	long	int_part;
	char	*decimal_point;

	decimal_point = ft_strchr(nptr, '.');
	if (!decimal_point)
		return (_atol(nptr));
	int_part = _atol(nptr);
	decimal = _atol(decimal_point + 1);
	decimal = decimal / pow(10, ndigs(decimal));
	if (int_part < 0 || (int_part == 0 && ft_strchr(nptr, '-')))
		return ((double)int_part - decimal);
	return ((double)int_part + decimal);
}
