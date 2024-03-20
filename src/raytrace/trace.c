/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/20 08:58:58 by dda-cunh         ###   ########.fr       */
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

	final_color = origin.color;
	apply_bias(&origin);

	ray = (t_ray3){origin.coords,
		normalize_vec3(vec3_from_points(origin.coords,
				program->light.coords))};
	collision = do_collisions(ray, program);
	if (valid_collision(collision.scalar))
		final_color = blend_colors(final_color, SHADOW_RATIO,
				(t_color){255, 0, 0, 0});
	else
		final_color = blend_colors(final_color,
				program->light.ratio, (t_color){255, 255, 255, 255});
	return (final_color);
}

void	trace(t_prog *program)
{
	t_color	new_color;
	t_image	buffer;
	int		curr_x;
	int		curr_y;

	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	curr_y = 0;
	while (curr_y < WINDOW_H)
	{
		curr_x = 0;
		while (curr_x < WINDOW_W)
		{
			if (valid_collision(program->collisions[curr_y][curr_x].scalar))
			{
				new_color = ray_to_lights(program->collisions[curr_y][curr_x],
						program);
				set_image_pixel(buffer, curr_x, curr_y, new_color);
			}
			curr_x++;
		}
		curr_y++;
	}
	dump_image_window(buffer);
}
