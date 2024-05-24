/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:44:43 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/24 02:34:38 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Calculates the collision point between a ray and the planes of
 	a cylinder object.
 *
 * @param ray	The ray to collide with the cylinder.
 * @param cy	The cylinder object to collide with.
 * @return		The collision point structure.
 */
static t_coll_point3	coll_cylinder_planes(t_ray3 ray, t_object_cylinder cy)
{
	t_coll_point3	coll1;
	t_coll_point3	coll2;

	coll1 = cy.disk1->collide(cy.disk1, ray);
	coll2 = cy.disk2->collide(cy.disk2, ray);
	if (valid_collision(coll1.scalar) && coll1.scalar < coll2.scalar)
		if (point3_distance_point3(point3_plus_vec3(ray.origin,
					scale_vec3(ray.direction, coll1.scalar)), cy.center)
			<= cy.radius)
			return (coll1);
	if (valid_collision(coll2.scalar))
		if (point3_distance_point3(point3_plus_vec3(ray.origin,
					scale_vec3(ray.direction, coll2.scalar)), cy.center)
			<= cy.radius)
			return (coll2);
	return (get_no_collision());
}

/**
 * Calculates the normal vector of a collision point on the "side"
 	of a cylinder object.
 *
 * @param self			The cylinder object.
 * @param coll_coords	The collision coordinates.
 * @return				The normal vector at the collision point.
 */
static t_coll_point3	get_side_coll(t_object_cylinder *self,
		t_point3 coll_coords, double t)
{
	t_vec3		center_to_coll;
	t_vec3		side_normal;

	center_to_coll = vec3_from_points(self->center, coll_coords);
	side_normal = normalize_vec3(vec3_sub(center_to_coll,
				scale_vec3(self->axis,
					vec3_dot_product(self->axis, center_to_coll))));
	return ((t_coll_point3)
		{
			coll_coords,
			self->color,
			(t_color){255, 0, 0, 0},
		side_normal,
		t
	});
}

/**
 * Calculates the collision point between a ray and a cylinder object.
 *
 * @param self	The cylinder object to collide with.
 * @param ray	The ray to collide with the cylinder.
 * @return		The collision point structure.
 */
static t_coll_point3	collide(t_object_cylinder *self, t_ray3 ray)
{
	t_point3	coll_coords;
	t_vec3		x;
	double		abc[3];
	double		t;

	x = vec3_sub(ray.origin, self->center);
	abc[0] = vec3_dot_product(self->axis, self->axis)
		- pow(vec3_dot_product(ray.direction, self->axis), 2);
	abc[1] = 2 * (vec3_dot_product(ray.direction, x)
			- (vec3_dot_product(ray.direction, self->axis)
				* vec3_dot_product(x, self->axis)));
	abc[2] = vec3_dot_product(x, x) - pow(vec3_dot_product(x, self->axis), 2)
		- pow(self->diameter / 2, 2);
	t = quadratic_smallest_pos(abc[0], abc[1], abc[2]);
	coll_coords = point3_plus_vec3(ray.origin, scale_vec3(ray.direction, t));
	if (valid_collision(t))
		if (point3_distance_point3(coll_coords, self->center) <= self->radius)
			return (get_side_coll(self, coll_coords, t));
	return (coll_cylinder_planes(ray, *self));
}

/**
 * Destroys a cylinder object and frees the memory.
 *
 * @param self	The cylinder object to destroy.
 */
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

/**
 * Creates a new cylinder object with the given parameters.
 *
 * @param cy	The parameters of the cylinder object.
 * @return		A pointer to the newly created cylinder object.
 */
t_object_cylinder	*new_cylinder(t_object_cylinder cy)
{
	t_object_cylinder	*obj;

	obj = ft_calloc(1, sizeof(t_object_cylinder));
	if (!obj)
		return (NULL);
	*obj = (t_object_cylinder){ID_CYLINDER, NULL, NULL, cy.center, cy.color,
		normalize_vec3(cy.axis), cy.diameter, cy.height, 0, destroy, collide};
	obj->radius = pythagorean_theorem(cy.height / 2, cy.diameter / 2);
	obj->disk1 = new_plane(point3_plus_vec3(cy.center,
				scale_vec3(obj->axis, cy.height / 2)), cy.color, obj->axis);
	if (!obj->disk1)
	{
		destroy(obj);
		return (NULL);
	}
	obj->disk2 = new_plane(point3_plus_vec3(cy.center,
				scale_vec3(obj->axis, -cy.height / 2)), cy.color, obj->axis);
	if (!obj->disk2)
	{
		destroy(obj);
		return (NULL);
	}
	return (obj);
}
