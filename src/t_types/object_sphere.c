/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:04:18 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/20 14:49:32 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Calculates the collision point between a ray and a sphere object.
 *
 * @param self	The sphere object.
 * @param ray	The ray to check for collision.
 * @return		The collision point structure.
 */
static t_coll_point3	collide(t_object_sphere *self, t_ray3 ray)
{
	t_point3	coll_coords;
	double		scalar;
	double		a;
	double		b;
	double		c;

	a = vec3_dot_product(ray.direction, ray.direction);
	b = 2 * vec3_dot_product(ray.direction, vec3_sub(ray.origin,
				self->center));
	c = vec3_dot_product(vec3_sub(ray.origin, self->center),
			vec3_sub(ray.origin, self->center)) - pow(self->diameter / 2, 2);
	scalar = quadratic_smallest_pos(a, b, c);
	if (!valid_collision(scalar))
		return (get_no_collision());
	coll_coords = point3_plus_vec3(ray.origin,
			scale_vec3(ray.direction, scalar));
	return ((t_coll_point3)
		{
			coll_coords,
			self->color,
			(t_color){255, 0, 0, 0},
		normalize_vec3(vec3_from_points(self->center, coll_coords)),
		scalar
	});
}

/**
 * Destroys a sphere object.
 *
 * @param self	The sphere object to destroy.
 */
static void	destroy(t_object_sphere *self)
{
	if (self)
		free(self);
}

/**
 * Creates a new sphere object.
 *
 * @param center	The center point of the sphere.
 * @param color		The color of the sphere.
 * @param diameter	The diameter of the sphere.
 * @return			The newly created sphere object.
 */
t_object_sphere	*new_sphere(t_point3 center, t_color color, double diameter)
{
	t_object_sphere	*obj;

	obj = ft_calloc(1, sizeof(t_object_sphere));
	if (!obj)
		return (NULL);
	*obj = (t_object_sphere)
	{
		ID_SPHERE,
		center,
		color,
		diameter,
		destroy,
		collide
	};
	return (obj);
}
