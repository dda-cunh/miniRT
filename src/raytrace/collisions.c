/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/18 16:37:54 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "stdio.h"	//FORBIDDEN IMPORT
#include <math.h>

static int	coll_cylinder(t_ray3 ray, t_collidable_entity cy_ent)
{
	t_object_cylinder	cy;

	cy = cy_ent.object.cy;
	return (ray.origin.x + *(int *)&cy.axis); //compilation flags placeholder
}

static int	coll_sphere(t_ray3 ray, t_collidable_entity sp_ent)
{
    t_object_sphere sp;
    double coll_scallar_1;
    double coll_scallar_2;
    double discriminant;
    double abc[3];

    sp = sp_ent.object.sp;
    abc[0] = vec3_dot_product(ray.direction, ray.direction);
    abc[1] = 2 * vec3_dot_product(ray.direction, vec3_sub(ray.origin, sp.center));
    abc[2] = vec3_dot_product(vec3_sub(ray.origin, sp.center), vec3_sub(ray.origin, sp.center)) - pow(sp.diameter / 2, 2);
    discriminant = pow(abc[1], 2) - 4 * abc[0] * abc[2];
    //printf("With ray{%f, %f, %f} got discr:%f\n", ray.direction.x, ray.direction.y, ray.direction.z, discriminant);
    if (discriminant >= 0)
    {
        coll_scallar_1 = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
        coll_scallar_2 = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
        if (coll_scallar_1 > coll_scallar_2)
            return (coll_scallar_2);
        return (coll_scallar_1);
    }
    return (-1);
}

static int	coll_plane(t_ray3 ray, t_collidable_entity pl_ent)
{
	t_object_plane	pl;
	double			plane_equation_app;

	pl = pl_ent.object.pl;
	plane_equation_app = pl.normal.x * (ray.origin.x - pl.point.x)
							+ pl.normal.y * (ray.origin.y - pl.point.y)
							+ pl.normal.z * (ray.origin.z - pl.point.z);
	if (plane_equation_app == 0)
		return (1);
	return (0);
}

static int	coll_func_wrapper(t_ray3 ray, t_collidable_entity	*curr_ent)
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
	double				curr_scalar;
	double				min_scalar;

	curr_node = program->collidables;
	min_coll_scalar = NULL;
	while (curr_node)
	{
		curr_ent = curr_node->content;
		curr_scalar = coll_func_wrapper(ray, curr_ent);
		if (!min_coll_scalar && curr_scalar > 0)
		{
			min_scalar = curr_scalar;
			min_coll_scalar = curr_ent;
		}
		else if (curr_scalar > 0 && curr_scalar < min_scalar)
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
