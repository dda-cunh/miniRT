/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/12 16:05:09 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"
#include "stdio.h"	//FORBIDDEN IMPORT

static int	belongs_cylinder(t_point3 point, t_collidable_entity cy_ent)
{
	t_object_cylinder	cy;

	cy = cy_ent.object.cy;
	return (point.x + *(int *)&cy.axis); //compilation flags placeholder
}

static int	belongs_sphere(t_point3 point, t_collidable_entity sp_ent)
{
	t_object_sphere	sp;

	sp = sp_ent.object.sp;
	if (point3_distance_point3(point , sp.center) <= (sp.diameter / 2))
	{
		printf("Collision: POINT(%f, %f, %f)\n", point.x, point.y, point.z); //FORBIDDEN FUNC
		return (color_to_int(sp.color));
	}
	return (0);
}

static int	belongs_plane(t_point3 point, t_collidable_entity pl_ent)
{
	t_object_plane	pl;
	float			plane_equation_app;

	pl = pl_ent.object.pl;
	plane_equation_app = pl.normal.x * (point.x - pl.point.x)
							+ pl.normal.y * (point.y - pl.point.y)
							+ pl.normal.z * (point.z - pl.point.z);
	if (plane_equation_app == 0)
		return (color_to_int(pl.color));
	return (0);
}

static int	get_collision(t_point3 point, t_prog *program)
{
	t_collidable_entity	*curr_ent;
	t_list				*curr_node;
	int					color;

	color = 0;
	curr_node = program->collidables;
	while (curr_node)
	{
		curr_ent = program->collidables->content;
		if (curr_ent->id == ID_CYLINDER)
			color = belongs_cylinder(point, *curr_ent);
		else if (curr_ent->id == ID_SPHERE)
			color = belongs_sphere(point, *curr_ent);
		else if (curr_ent->id == ID_PLANE)
			color = belongs_plane(point, *curr_ent);
		curr_node = curr_node->next;
		if (color)
			break ;
	}
	return (color);
}

int	do_collisions(t_ray3 ray, t_prog *program)
{
	const float	scalar_increment = 0.5;	//TBD
	const float	scalar_max = 20.5;		//TBD
	float		scalar;
	int			color;

	scalar = scalar_increment;
	while (scalar < scalar_max)
	{
		color = get_collision(point3_plus_vec3(ray.origin,
					scale_vec3(ray.direction, scalar)), program);
		if (color)
			return (color);
		scalar += scalar_increment;
	}
	return (0);
}
