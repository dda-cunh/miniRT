/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:56:54 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/22 16:49:19 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_color	trace(int x, int y, t_prog *program)
{
	t_vec3	ray_direction;
	float	ndc_xy[2];
	float	view_x;
	float	view_y;

	ndc_xy[0] = (2.0f * x) / WINDOW_W - 1.0f;
	ndc_xy[1] = 1.0f - (2.0f * y) / WINDOW_H;
	view_x = ndc_xy[0] * ((float)WINDOW_W / (float)WINDOW_H)
		* program->camera.tan_fov;
	view_y = ndc_xy[1] * program->camera.tan_fov;
	ray_direction.x = view_x * program->camera.right.x + view_y
		* program->camera.up.x + program->camera.forward.x;
	ray_direction.y = view_x * program->camera.right.y + view_y
		* program->camera.up.y + program->camera.forward.y;
	ray_direction.z = view_x * program->camera.right.z + view_y
		* program->camera.up.z + program->camera.forward.z;
	return (do_collisions((t_ray3){program->camera.coords,
			normalize_vec3(ray_direction)}, program));
}

t_image	do_rays(t_prog *program)
{
	t_image	buffer;
	t_color	color;
	int		curr_y;
	int		curr_x;

	curr_y = 0;
	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	while (curr_y < WINDOW_H)
	{
		curr_x = 0;
		while (curr_x < WINDOW_W)
		{
			color = trace(curr_x, curr_y, program);
			set_image_pixel(buffer, curr_x, curr_y, color);
			curr_x++;
		}
		curr_y++;
	}
	return (buffer);
}
