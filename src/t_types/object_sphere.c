/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:04:18 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/17 16:05:59 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static float	collide(t_object_sphere *self, t_ray3 ray)
{
	float	a;
	float	b;
	float	c;

	a = vec3_dot_product(ray.direction, ray.direction);
	b = 2 * vec3_dot_product(ray.direction, vec3_sub(ray.origin,
				self->center));
	c = vec3_dot_product(vec3_sub(ray.origin, self->center),
			vec3_sub(ray.origin, self->center)) - pow(self->diameter / 2, 2);
	return (quadratic_smallest_pos(a, b, c));
}

static void	destroy(t_object_sphere *self)
{
	if (self)
		free(self);
}

t_object_sphere	*new_sphere(t_point3 center, t_color color, float diameter)
{
	t_object_sphere	*obj;

	obj = ft_calloc(1, sizeof(t_object_sphere));
	if (!obj)
		return (NULL);
	*obj = (t_object_sphere){ID_SPHERE, center, color, diameter, destroy,
			collide};
	return (obj);
}
