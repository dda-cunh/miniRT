/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:15:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/15 13:33:26 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

float	pythagorean_theorem(float a, float b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

float	quadratic_smallest_pos(float a, float b, float c)
{
	float	discriminant;
	float	sol1;
	float	sol2;

	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant >= 0)
	{
		sol1 = (-b + sqrt(discriminant)) / (2 * a);
		if (discriminant == 0)
			return (sol1);
		sol2 = (-b - sqrt(discriminant)) / (2 * a);
		if (sol1 > sol2)
			return (sol2);
		return (sol1);
	}
	return (-1);
}
