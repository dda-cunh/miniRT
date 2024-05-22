/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:15:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 19:39:16 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_math.h"

/**
 * Clamps a value between a minimum and maximum range.
 *
 * @param value	The value to be clamped.
 * @param min	The minimum value of the range.
 * @param max	The maximum value of the range.
 * @return		The clamped value.
 */
double	clamp_value(double value, double min, double max)
{
	return (fmax(min, fmin(max, value)));
}

/**
 * Calculates the hypotenuse of a right triangle using the Pythagorean theorem.
 *
 * @param a	The length of one of the triangle's legs.
 * @param b	The length of the other leg.
 * @return	The length of the hypotenuse.
 */
double	pythagorean_theorem(double a, double b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

/**
 * Calculates the smallest positive solution of a quadratic equation.
 *
 * @param a	The coefficient of the quadratic term.
 * @param b	The coefficient of the linear term.
 * @param c	The constant term.
 * @return	The smallest positive solution of the quadratic equation,
 				or -1 if no positive solution exists.
 */
double	quadratic_smallest_pos(double a, double b, double c)
{
	double	discriminant;
	double	discri_sqrt;
	double	sol1;
	double	sol2;

	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant >= 0)
	{
		discri_sqrt = sqrt(discriminant);
		sol1 = (-b + discri_sqrt) / (2 * a);
		if (discriminant == 0)
			return (sol1);
		sol2 = (-b - discri_sqrt) / (2 * a);
		if (sol1 > sol2)
			return (sol2);
		return (sol1);
	}
	return (-1);
}
