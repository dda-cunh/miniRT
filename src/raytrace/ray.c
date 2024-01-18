/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:56:54 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/18 14:57:55 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static int	trace(int x, int y, t_prog *program)
{
	double	view_x;
	double	view_y;
	double	ndcX;
	double	ndcY;

	ndcX = (2.0f * x) / WINDOW_W - 1.0f;
	ndcY = 1.0f - (2.0f * y) / WINDOW_H;
	double tanFOV = tanf(program->camera.fov * 0.5f * (M_PI / 180.0f));
	view_x = ndcX * ((double)WINDOW_W / (double)WINDOW_H) * tanFOV;
	view_y = ndcY * tanFOV;
	t_vec3 forward = normalize_vec3(program->camera.look_direction);
	t_vec3 right = normalize_vec3(vec3_cross_product(forward, (t_vec3){0.0f, 1.0f, 0.0f}));
	t_vec3 up = vec3_cross_product(right, forward);
	t_vec3 rayDirection;
	rayDirection.x = view_x * right.x + view_y * up.x + forward.x;
	rayDirection.y = view_x * right.y + view_y * up.y + forward.y;
	rayDirection.z = view_x * right.z + view_y * up.z + forward.z;
	return do_collisions((t_ray3){program->camera.coords,
		normalize_vec3(rayDirection)}, program);
}



void	do_rays(t_prog *program)
{
	t_image	buffer;
	int		curr_y;
	int		curr_x;
	int		color;

	curr_y = 0;
	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	while (curr_y < WINDOW_H)
	{
		curr_x = 0;
		while (curr_x < WINDOW_W)
		{
			color = trace(curr_x, curr_y, program);
			set_image_pixel(buffer, curr_x, curr_y, int_to_color(color));
			curr_x++;
		}
		curr_y++;
	}
	mlx_put_image_to_window(program->mlx_ptr, program->win_ptr,
			buffer.ptr, 0, 0);
	mlx_destroy_image(buffer.win.mlx_ptr, buffer.ptr);
	return ;
}
