/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:16:45 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/04/27 11:25:04 by dda-cunh         ###   ########.fr       */
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

double	vec3_dot_product(t_vec3 a, t_vec3 b)
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

t_vec3	scale_vec3(t_vec3 vector, double scalar)
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
