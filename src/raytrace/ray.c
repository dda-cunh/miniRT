/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:56:54 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/10 20:44:47 by dda-cunh         ###   ########.fr       */
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

void	do_rays(t_prog *prog)
{
	t_coll_point3	*coll;
	int				curr_y;
	int				curr_x;

	prog->collisions = ft_calloc(WINDOW_H, sizeof(t_coll_point3 *));
	if (!prog->collisions)
		return ;
	curr_y = -1;
	while (++curr_y < WINDOW_H)
	{
		curr_x = -1;
		prog->collisions[curr_y] = ft_calloc(WINDOW_W, sizeof(t_coll_point3));
		while (++curr_x < WINDOW_W)
		{
			coll = &(prog->collisions[curr_y][curr_x]);
			*coll = do_ray(curr_x, curr_y, prog);
			if (valid_collision(coll->scalar))
				coll->visible_color = (t_color){coll->coll_color.alpha,
					prog->ambient_l.color.red * (coll->coll_color.red / 255.0),
					prog->ambient_l.color.green
					* (coll->coll_color.green / 255.0),
					prog->ambient_l.color.blue
					* (coll->coll_color.blue / 255.0)};
		}
	}
}
