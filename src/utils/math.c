/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:43:28 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/12 13:28:30 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

float	point3_distance_point3(t_point3 p1, t_point3 p2)
{
	return (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)
			+ pow((p2.z - p1.z), 2)));
}

t_point3	point3_plus_vec3(t_point3 point, t_vec3 vector)
{
	return ((t_point3)
		{
			point.x + vector.x,
			point.x + vector.y,
			point.x + vector.z
		});
}

t_vec3	scale_vec3(t_vec3 vector, float scalar)
{
	return ((t_vec3)
		{
			vector.x * scalar,
			vector.y * scalar,
			vector.z * scalar
		});
}

t_vec3	normalize_vec3(t_vec3 vector)
{
	double	magnitude;

	magnitude = sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z);
	return ((t_vec3)
		{
			vector.x / magnitude,
			vector.y / magnitude,
			vector.z / magnitude
		});
}
