/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/20 14:30:38 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Applies a bias to the collision point coordinates.
 *
 * @param point	The collision point to apply the bias to.
 */
static void	apply_bias(t_coll_point3 *point)
{
	point->coords.x = point->normal.x * SHADOW_BIAS + point->coords.x;
	point->coords.y = point->normal.y * SHADOW_BIAS + point->coords.y;
	point->coords.z = point->normal.z * SHADOW_BIAS + point->coords.z;
}

/**
 * Calculates the shading of a pixel considering the lights.
 *
 * @param origin	The collision point visible in the scene.
 * @param program	The program containing the light source and colidables.
 * @return			The final color the pixel should have.
 */
static t_color	ray_to_lights(t_coll_point3 origin, t_prog *program)
{
	t_coll_point3	collision;
	t_color			final_color;
	t_ray3			ray;
	double			max_dist;
	bool			valid_coll;

	apply_bias(&origin);
	final_color = origin.visible_color;
	max_dist = point3_distance_point3(origin.coords, program->light.coords)
		- SHADOW_BIAS;
	ray = (t_ray3){origin.coords,
		normalize_vec3(vec3_from_points(origin.coords,
				program->light.coords))};
	collision = do_collisions(ray, program);
	valid_coll = valid_collision(collision.scalar)
		&& collision.scalar <= max_dist;
	if (!valid_coll)
		final_color = lighting(origin, ray.direction, program->light);
	return (final_color);
}

/**
 * Traces rays and calculates the visible colors for each pixel in
 	the program's collision grid.
 *
 * @param program	The program containing the collision grid and other data.
 */
void	trace(t_prog *program)
{
	t_coll_point3	*coll;
	t_image			buffer;
	int				curr_x;
	int				curr_y;

	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	curr_y = 0;
	while (curr_y < WINDOW_H)
	{
		curr_x = 0;
		while (curr_x < WINDOW_W)
		{
			coll = &program->collisions[curr_y][curr_x];
			if (valid_collision(coll->scalar))
			{
				coll->visible_color = ray_to_lights(*coll, program);
				set_image_pixel(buffer, curr_x, curr_y, coll->visible_color);
			}
			curr_x++;
		}
		curr_y++;
	}
	dump_image_window(buffer);
}
