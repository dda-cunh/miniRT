/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:45 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 19:39:28 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_math.h"

/**
 * Calculates the cross product of two 3D vectors.
 *
 * @param a	The first vector.
 * @param b	The second vector.
 * @return	The cross product of the two vectors.
 */
t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	return ((t_vec3)
		{
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		});
}

/**
 * Calculates the dot product of two 3D vectors.
 *
 * @param a	The first vector.
 * @param b	The second vector.
 * @return	The dot product of the two vectors.
 */
double	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/**
 * Subtracts two 3D vectors.
 *
 * @param a	The first vector.
 * @param b	The second vector.
 * @return	The result of the subctration.
 */
t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3)
		{
			a.x - b.x,
			a.y - b.y,
			a.z - b.z
		});
}

/**
 * Scales a 3D vector by a scalar value.
 *
 * @param vector	The vector to scale.
 * @param scalar	The scalar value to multiply the vector by.
 * @return			The scaled vector.
 */
t_vec3	scale_vec3(t_vec3 vector, double scalar)
{
	return ((t_vec3)
		{
			vector.x * scalar,
			vector.y * scalar,
			vector.z * scalar
		});
}

/**
 * Normalizes a 3D vector.
 *
 * @param vector	The vector to normalize.
 * @return			The normalized vector.
 */
t_vec3	normalize_vec3(t_vec3 vector)
{
	double	magnitude;

	magnitude = sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2));
	if (magnitude == 0)
		return ((t_vec3){0, 0, 0});
	return ((t_vec3)
		{
			vector.x / magnitude,
			vector.y / magnitude,
			vector.z / magnitude
		});
}
