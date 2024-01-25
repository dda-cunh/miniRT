/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:43:28 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/25 15:30:02 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	return (t_vec3)
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};
}

float	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	point3_distance_point3(t_point3 p1, t_point3 p2)
{
	return (sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2)
			+ pow((p2.z - p1.z), 2)));
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3)
		{
			a.x - b.x,
			a.y - b.y,
			a.z - b.z
		});
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
	float	magnitude;

	magnitude = sqrt(vector.x * vector.x + vector.y * vector.y
			+ vector.z * vector.z);
	return ((t_vec3)
		{
			vector.x / magnitude,
			vector.y / magnitude,
			vector.z / magnitude
		});
}
