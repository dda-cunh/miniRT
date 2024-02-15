/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/15 17:47:27 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_color	get_coll_entity_color(t_collidable_entity *ent)
{
	if (ent->id == ID_CYLINDER)
		return (ent->object->cy->color);
	else if (ent->id == ID_SPHERE)
		return (ent->object->sp->color);
	else if (ent->id == ID_PLANE)
		return (ent->object->pl->color);
	return ((t_color){0, 0, 0, 0});
}

static float	coll_func_wrapper(t_ray3 ray, t_collidable_entity *curr_ent)
{
	if (curr_ent)
	{
		if (curr_ent->id == ID_CYLINDER)
			return (curr_ent->object->cy->collide(curr_ent->object->cy, ray));
		else if (curr_ent->id == ID_SPHERE)
			return (curr_ent->object->sp->collide(curr_ent->object->sp, ray));
		else if (curr_ent->id == ID_PLANE)
			return (curr_ent->object->pl->collide(curr_ent->object->pl, ray));
	}
	return (-1);
}

t_color	do_collisions(t_ray3 ray, t_prog *program)
{
	t_coll_entity_list	*curr_node;
	t_color				min_coll_scalar;
	float				curr_scalar;
	float				min_scalar;

	curr_node = program->collidables;
	min_coll_scalar = (t_color){0, 0, 0, 0};
	min_scalar = INFINITY;
	while (curr_node)
	{
		curr_scalar = coll_func_wrapper(ray, curr_node->ent);
		if (curr_scalar >= EPSILON && curr_scalar < min_scalar)
		{
			min_scalar = curr_scalar;
			min_coll_scalar = get_coll_entity_color(curr_node->ent);
		}
		curr_node = curr_node->next;
	}
	return (min_coll_scalar);
}
