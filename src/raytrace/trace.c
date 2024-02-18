/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:26:59 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/18 12:52:36 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_color	ray_to_lights(t_coll_point3 origin, t_prog *program)
{
	t_coll_point3	collision;
	t_color			final_color;
	t_light			*light;
	t_list			*curr_node;
	t_ray3			ray;

	curr_node = program->lights;
	final_color = origin.color;
	while (curr_node)
	{
		light = curr_node->content;
		ray = (t_ray3){origin.coords,
			normalize_vec3(vec3_from_points(origin.coords, light->coords))};
		collision = do_collisions(ray, program);
		if (collision.scalar > EPSILON)
			final_color = darken_color(final_color, SHADOW_RATIO);
		// else
		// 	final_color = brightness(final_color, light->ratio);
		curr_node = curr_node->next;
	}
	return (final_color);
}

void	trace(t_prog *program)
{
	t_color	new_color;
	t_image buffer;
	int		curr_x;
	int		curr_y;

	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	curr_y = 0;
	while (curr_y < WINDOW_H)
	{
		curr_x = 0;
		while (curr_x < WINDOW_W)
		{
			if (program->collisions[curr_y][curr_x].scalar > EPSILON)
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
