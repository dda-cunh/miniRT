/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:17:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/15 13:33:40 by dda-cunh         ###   ########.fr       */
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
	return (sqrt(pow(point.x - sphere.center.x, 2)
			+ pow(point.y - sphere.center.y, 2)
			+ pow(point.z - sphere.center.z, 2)) <= (sphere.diameter / 2));
}

float	point3_distance_point3(t_point3 p1, t_point3 p2)
{
	return (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)
			+ pow((p2.z - p1.z), 2)));
}
