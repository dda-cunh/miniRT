/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:56:54 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/18 12:47:33 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_coll_point3	do_ray(int x, int y, t_prog *program)
{
	t_vec3	ray_direction;
	double	ndc_xy[2];
	double	view_x;
	double	view_y;

	ndc_xy[0] = (2.0f * x) / WINDOW_W - 1.0f;
	ndc_xy[1] = 1.0f - (2.0f * y) / WINDOW_H;
	view_x = ndc_xy[0] * ((double)WINDOW_W / (double)WINDOW_H)
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

t_coll_point3	**do_rays(t_prog *program)
{
	t_coll_point3	**collision;
	t_image			buffer;
	int				curr_y;
	int				curr_x;

	curr_y = 0;
	collision = ft_calloc(WINDOW_H, sizeof(t_coll_point3 *));
	if (!collision)
		return (NULL);
	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	while (curr_y < WINDOW_H)
	{
		curr_x = 0;
		collision[curr_y] = ft_calloc(WINDOW_W, sizeof(t_coll_point3));
		while (curr_x < WINDOW_W)
		{
			collision[curr_y][curr_x] = do_ray(curr_x, curr_y, program);
			set_image_pixel(buffer, curr_x, curr_y,
				collision[curr_y][curr_x].color);
			curr_x++;
		}
		curr_y++;
	}
	dump_image_window(buffer);
	return (collision);
}
