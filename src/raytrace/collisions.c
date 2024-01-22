/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/22 16:11:27 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "stdio.h"	//FORBIDDEN IMPORT

static float	coll_cylinder(t_ray3 ray, t_collidable_entity cy_ent)
{
	t_object_cylinder	cy;

	cy = cy_ent.object.cy;
	return (ray.origin.x + *(int *)&cy.axis); //compilation flags placeholder
}

static float	coll_sphere(t_ray3 ray, t_collidable_entity sp_ent)
{
	t_object_sphere sp;
	float			coll_scallar_1;
	float			coll_scallar_2;
	float			discriminant;
	float			abc[3];

	sp = sp_ent.object.sp;
	abc[0] = vec3_dot_product(ray.direction, ray.direction);
	abc[1] = 2 * vec3_dot_product(ray.direction, vec3_sub(ray.origin, sp.center));
	abc[2] = vec3_dot_product(vec3_sub(ray.origin, sp.center), vec3_sub(ray.origin, sp.center)) - pow(sp.diameter / 2, 2);
	discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
	if (discriminant >= 0)
	{
		coll_scallar_1 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
		if (discriminant == 0)
			return (coll_scallar_1);
		coll_scallar_2 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
		if (coll_scallar_1 > coll_scallar_2)
			return (coll_scallar_2);
		return (coll_scallar_1);
	}
	return (-1);
}

static float	coll_plane(t_ray3 ray, t_collidable_entity pl_ent)
{
	t_object_plane	pl;
	float			scallar;
	float			denom;

	pl = pl_ent.object.pl;
	scallar = -1;
	denom = vec3_dot_product(pl.normal, ray.direction);
	if (denom > EPSILON || denom < -EPSILON)
		scallar = vec3_dot_product(vec3_sub(pl.point, ray.origin), pl.normal)
					/ denom;
	return (scallar);
}

static float	coll_func_wrapper(t_ray3 ray, t_collidable_entity	*curr_ent)
{
	if (curr_ent->id == ID_CYLINDER)
		return (coll_cylinder(ray, *curr_ent));
	else if (curr_ent->id == ID_SPHERE)
		return (coll_sphere(ray, *curr_ent));
	else if (curr_ent->id == ID_PLANE)
		return (coll_plane(ray, *curr_ent));
	return (-1);
}

t_color	do_collisions(t_ray3 ray, t_prog *program)
{
	t_collidable_entity	*min_coll_scalar;
	t_collidable_entity	*curr_ent;
	t_list				*curr_node;
	float				curr_scalar;
	float				min_scalar;

	curr_node = program->collidables;
	min_coll_scalar = NULL;
	while (curr_node)
	{
		curr_ent = curr_node->content;
		curr_scalar = coll_func_wrapper(ray, curr_ent);
		if (!min_coll_scalar && curr_scalar >= 0)
		{
			min_scalar = curr_scalar;
			min_coll_scalar = curr_ent;
		}
		else if (curr_scalar >= 0 && curr_scalar < min_scalar)
		{
			min_scalar = curr_scalar;
			min_coll_scalar = curr_ent;
		}
		curr_node = curr_node->next;
	}
	if (min_coll_scalar)
		return (min_coll_scalar->object.cy.color);
	return ((t_color){0, 0, 0, 0});
}
