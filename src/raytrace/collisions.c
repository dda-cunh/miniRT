/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/11 12:28:43 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Returns a collision point structure representing no collision.
 * 
 * @return	The collision point structure with default values.
 */
t_coll_point3	get_no_collision(void)
{
	return ((t_coll_point3)
		{
			(t_point3){0, 0, 0}, (t_color){0, 0, 0, 0},
			(t_color){0, 0, 0, 0},
			(t_point3){0, 0, 0},
			INFINITY
		});
}

/**
 * Wrapper function to call the appropriate collision function
 	based on the collidable shape type.
 * 
 * @param ray		The ray to check for collision.
 * @param curr_ent	The current collidable shape.
 * @return			The collision point structure representing the collision.
 */
static t_coll_point3	coll_func_wrapper(t_ray3 ray,
	t_collidable_shape *curr_ent)
{
	t_collidable_id	id;

	if (curr_ent)
	{
		id = get_coll_shape_id(*curr_ent);
		if (id == ID_CYLINDER)
			return (curr_ent->cy->collide(curr_ent->cy, ray));
		else if (id == ID_SPHERE)
			return (curr_ent->sp->collide(curr_ent->sp, ray));
		else if (id == ID_PLANE)
			return (curr_ent->pl->collide(curr_ent->pl, ray));
	}
	return (get_no_collision());
}

/**
 * Checks if a collision scalar value is considered valid.
 * 
 * @param scalar	The collision scalar value to check.
 * @return			True if the scalar is valid, false otherwise.
 */
bool	valid_collision(double scalar)
{
	return (scalar >= EPSILON && scalar < INFINITY);
}

/**
 * Performs collision detection for a ray with a list of collidable shapes.
 * 
 * @param ray		The ray to check for collision.
 * @param program	The program containing the list of collidable shapes.
 * @return			The collision point structure representing the closest collision.
 */
t_coll_point3	do_collisions(t_ray3 ray, t_prog *program)
{
	t_collidable_shape	*collidable;
	t_coll_point3		curr_coll;
	t_coll_point3		min_coll;
	size_t				i;

	min_coll = get_no_collision();
	i = 0;
	while (i < program->collidables->length)
	{
		collidable = program->collidables->get(program->collidables, i);
		curr_coll = coll_func_wrapper(ray, collidable);
		if (valid_collision(curr_coll.scalar)
			&& curr_coll.scalar < min_coll.scalar)
			min_coll = curr_coll;
		i++;
	}
	return (min_coll);
}
