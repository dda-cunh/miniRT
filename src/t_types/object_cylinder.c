/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:43 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/17 16:05:59 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static float	coll_cylinder_planes(t_ray3 ray, t_object_cylinder cy)
{
	float			coll1;
	float			coll2;

	coll1 = cy.disk1->collide(cy.disk1, ray);
	coll2 = cy.disk2->collide(cy.disk2, ray);
	if (coll1 > EPSILON && coll1 < coll2)
		if (point3_distance_point3(point3_plus_vec3(ray.origin,
					scale_vec3(ray.direction, coll1)), cy.center)
			< pythagorean_theorem(cy.height / 2, cy.diameter / 2))
			return (coll1);
	if (coll2 > EPSILON)
		if (point3_distance_point3(point3_plus_vec3(ray.origin,
					scale_vec3(ray.direction, coll2)), cy.center)
			< pythagorean_theorem(cy.height / 2, cy.diameter / 2))
			return (coll2);
	return (-1);
}

static float	collide(t_object_cylinder *self, t_ray3 ray)
{
	t_vec3	x;
	float	abc[3];
	float	t;

	x = vec3_sub(ray.origin, self->center);
	abc[0] = vec3_dot_product(self->axis, self->axis)
		- powf(vec3_dot_product(ray.direction, self->axis), 2);
	abc[1] = 2 * (vec3_dot_product(ray.direction, x)
			- (vec3_dot_product(ray.direction, self->axis)
				* vec3_dot_product(x, self->axis)));
	abc[2] = vec3_dot_product(x, x) - powf(vec3_dot_product(x, self->axis), 2)
		- powf(self->diameter / 2, 2);
	t = quadratic_smallest_pos(abc[0], abc[1], abc[2]);
	if (t > 0)
		if (point3_distance_point3(point3_plus_vec3(ray.origin,
					scale_vec3(ray.direction, t)), self->center)
			< pythagorean_theorem(self->height / 2, self->diameter / 2))
			return (t);
	return (coll_cylinder_planes(ray, *self));
}

static void	destroy(t_object_cylinder *self)
{
	if (self)
	{
		if (self->disk1)
			self->disk1->destroy(self->disk1);
		if (self->disk2)
			self->disk2->destroy(self->disk2);
		free (self);
	}
}

t_object_cylinder	*new_cylinder(t_object_cylinder cy)
{
	t_object_cylinder	*obj;

	obj = ft_calloc(1, sizeof(t_object_cylinder));
	if (!obj)
		return (NULL);
	*obj = (t_object_cylinder){ID_CYLINDER, NULL, NULL, cy.center, cy.color,
		cy.axis, cy.diameter, cy.height, destroy, collide};
	obj->disk1 = new_plane(point3_plus_vec3(cy.center,
				scale_vec3(cy.axis, cy.height / 2)), cy.color, cy.axis);
	if (!obj->disk1)
	{
		destroy(obj);
		return (NULL);
	}
	obj->disk2 = new_plane(point3_plus_vec3(cy.center,
				scale_vec3(cy.axis, -cy.height / 2)), cy.color, cy.axis);
	if (!obj->disk2)
	{
		destroy(obj);
		return (NULL);
	}
	return (obj);
}
