/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/04/25 16:44:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static	void	apply_bias(t_coll_point3 *point)
{
	point->coords.x = point->normal.x * SHADOW_BIAS + point->coords.x;
	point->coords.y = point->normal.y * SHADOW_BIAS + point->coords.y;
	point->coords.z = point->normal.z * SHADOW_BIAS + point->coords.z;
}

static t_color	ray_to_lights(t_coll_point3 origin, t_prog *program)
{
	t_coll_point3	collision;
	t_color			final_color;
	t_ray3			ray;
	double			max_dist;
	bool			valid_coll;

	apply_bias(&origin);
	final_color = origin.visible_color;
	max_dist = point3_distance_point3(origin.coords, program->light.coords);
	ray = (t_ray3){origin.coords,
		normalize_vec3(vec3_from_points(origin.coords,
				program->light.coords))};
	collision = do_collisions(ray, program);
	valid_coll = valid_collision(collision.scalar)
					&& collision.scalar <= max_dist;
	if (!valid_coll)
		final_color = blend_colors(final_color,
				program->light.ratio, program->light.color);
	return (final_color);
}

static void	apply_ambient(t_coll_point3	*coll, t_light ambient_l)
{
		coll->visible_color = blend_colors(coll->visible_color,
			ambient_l.ratio, ambient_l.color);
		coll->visible_color = blend_colors(coll->visible_color,
			ambient_l.ratio, coll->coll_color);
}

void	trace(t_prog *program)
{
	t_coll_point3	*coll;
	t_color			new_color;
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
				apply_ambient(coll, program->ambient_l);
				new_color = ray_to_lights(*coll, program);
				set_image_pixel(buffer, curr_x, curr_y, new_color);
			}
			curr_x++;
		}
		curr_y++;
	}
	dump_image_window(buffer);
}
