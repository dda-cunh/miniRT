/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/18 20:11:55 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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
	return (NO_COLLISION);
}

bool	valid_collision(double scalar)
{
	return (scalar >= EPSILON && scalar < INFINITY);
}

t_coll_point3	do_collisions(t_ray3 ray, t_prog *program)
{
	t_coll_shape_list	*curr_node;
	t_coll_point3		curr_coll;
	t_coll_point3		min_coll;

	min_coll = NO_COLLISION;
	curr_node = program->collidables;
	while (curr_node)
	{
		curr_coll = coll_func_wrapper(ray, curr_node->ent);
		if (valid_collision(curr_coll.scalar)
			&& curr_coll.scalar < min_coll.scalar)
			min_coll = curr_coll;
		curr_node = curr_node->next;
	}
	return (min_coll);
}
