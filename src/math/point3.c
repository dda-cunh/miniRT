/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:17:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/11 12:03:40 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Adds a vector to a point and returns the resulting point.
 *
 * @param point		The point to be added.
 * @param vector	The vector to be added.
 * @return			The resulting point after adding the vector.
 */
t_point3	point3_plus_vec3(t_point3 point, t_vec3 vector)
{
	return ((t_point3)
		{
			point.x + vector.x,
			point.y + vector.y,
			point.z + vector.z
		});
}

/**
 * Checks if a point is inside a sphere.
 *
 * @param point		The point to check.
 * @param sphere	The sphere to check against.
 * @return			True if the point is inside the sphere, false otherwise.
 */
bool	point3_inside_sphere(t_point3 point, t_object_sphere sphere)
{
	return (sqrt(pow(point.x - sphere.center.x, 2)
			+ pow(point.y - sphere.center.y, 2)
			+ pow(point.z - sphere.center.z, 2)) <= (sphere.diameter / 2));
}

/**
 * Calculates the vector from the start point to the end point.
 *
 * @param start	The starting point.
 * @param end	The ending point.
 * @return		The vector from the start point to the end point.
 */
t_vec3	vec3_from_points(t_point3 start, t_point3 end)
{
	return (vec3_sub(end, start));
}

/**
 * Calculates the Euclidean distance between two 3D points.
 *
 * @param p1	The first point.
 * @param p2	The second point.
 * @return		The distance between the two points.
 */
double	point3_distance_point3(t_point3 p1, t_point3 p2)
{
	return (sqrt(pow((p2.x - p1.x), 2)
			+ pow((p2.y - p1.y), 2)
			+ pow((p2.z - p1.z), 2)));
}
