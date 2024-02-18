/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:17:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/18 13:27:34 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_point3	point3_plus_vec3(t_point3 point, t_vec3 vector)
{
	return ((t_point3)
		{
			point.x + vector.x,
			point.y + vector.y,
			point.z + vector.z
		});
}

bool	point3_inside_sphere(t_point3 point, t_object_sphere sphere)
{
	return (sqrt(powf(point.x - sphere.center.x, 2)
			+ powf(point.y - sphere.center.y, 2)
			+ powf(point.z - sphere.center.z, 2)) <= (sphere.diameter / 2));
}

t_vec3	vec3_from_points(t_point3 start, t_point3 end)
{
	return (vec3_sub(end, start));
}

double	point3_distance_point3(t_point3 p1, t_point3 p2)
{
	return (sqrt(powf((p2.x - p1.x), 2) + powf((p2.y - p1.y), 2)
			+ powf((p2.z - p1.z), 2)));
}
