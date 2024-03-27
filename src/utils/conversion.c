/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:30:37 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/27 16:45:36 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/// @brief This function is part of the atof. It accumulates
/// the value of the characthers set representation and returns
/// it.
/// @param str 
/// @param sign 
/// @param dot 
/// @return 
static double	atof_acc(char *str, int sign, int dot)
{
	double	res;
	double	fractional;

	res = 0;
	fractional = 1;
	while (str && (ft_isdigit(*str) || *str == '.'))
	{
		if (*str == '.' && !dot)
		{
			str++;
			dot = 1;
		}
		if (dot)
		{
			fractional /= 10;
			res += (*str++ - 48) * fractional;
		}
		else
			res = res * 10.0 + *str++ - 48;
	}
	return (res * sign);
}

/// @brief This function converts a ascii representation of
/// a double and returns it as a double.
/// @param str 
/// @return 
double	ft_atof(char *str)
{
	double	sign;

	sign = 1;
	while (str && ft_isspace(*str))
		str++;
	if (str && (*str == '-' || *str == '+'))
		if (*str++ == '-')
			sign = -1;
	return (atof_acc(str, sign, 0));
}
