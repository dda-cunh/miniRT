/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/17 18:56:21 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_color	get_coll_entity_color(t_collidable_shape *ent)
{
	t_collidable_id	id;

	id = get_coll_shape_id(ent);
	if (id == ID_CYLINDER)
		return (ent->cy->color);
	else if (id == ID_SPHERE)
		return (ent->sp->color);
	else if (id == ID_PLANE)
		return (ent->pl->color);
	return ((t_color){0, 0, 0, 0});
}

static float	coll_func_wrapper(t_ray3 ray, t_collidable_shape *curr_ent)
{
	t_collidable_id	id;

	id = get_coll_shape_id(curr_ent);
	if (curr_ent)
	{
		if (id == ID_CYLINDER)
			return (curr_ent->cy->collide(curr_ent->cy, ray));
		else if (id == ID_SPHERE)
			return (curr_ent->sp->collide(curr_ent->sp, ray));
		else if (id == ID_PLANE)
			return (curr_ent->pl->collide(curr_ent->pl, ray));
	}
	return (-1);
}

t_coll_point3	do_collisions(t_ray3 ray, t_prog *program)
{
	t_coll_shape_list	*curr_node;
	t_color				color_min;
	float				curr_scalar;
	float				min_scalar;

	curr_node = program->collidables;
	color_min = (t_color){0, 0, 0, 0};
	min_scalar = INFINITY;
	while (curr_node)
	{
		curr_scalar = coll_func_wrapper(ray, curr_node->ent);
		if (curr_scalar >= EPSILON && curr_scalar < min_scalar)
		{
			min_scalar = curr_scalar;
			color_min = get_coll_entity_color(curr_node->ent);
		}
		curr_node = curr_node->next;
	}
	if (min_scalar == INFINITY)
		return ((t_coll_point3){ORIGIN, color_min, -1});
	return ((t_coll_point3){point3_plus_vec3(ray.origin,
			scale_vec3(ray.direction, min_scalar)), color_min, min_scalar});
}
