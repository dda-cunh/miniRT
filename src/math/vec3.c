/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:45 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/17 16:05:59 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vec3	vec3_cross_product(t_vec3 a, t_vec3 b)
{
	return ((t_vec3)
		{
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		});
}

float	vec3_dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
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
