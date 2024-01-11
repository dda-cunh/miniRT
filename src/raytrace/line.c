/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:56:54 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/11 13:22:01 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static int	ray(int x, int y, t_prog *program)
{
	return ((x + y + *(int *)program->mlx_ptr)); //placeholder
	//TODO COLLISIONS
	return (0);
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
			color = ray(curr_x, curr_y, program);
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
