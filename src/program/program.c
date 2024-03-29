/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:51:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/29 19:34:13 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	killprogram(int keycode, t_prog *program)
{
	if (program->collidables)
		program->collidables->destroy(program->collidables);
	if (program->collisions)
		free_matrix((void **)program->collisions, WINDOW_H);
	if (program->win_ptr)
		mlx_destroy_window(program->mlx_ptr, program->win_ptr);
	if (program->mlx_ptr)
	{
		mlx_loop_end(program->mlx_ptr);
		mlx_destroy_display(program->mlx_ptr);
		free(program->mlx_ptr);
	}
	exit(__on_exit(keycode, NULL));
}

t_prog	*get_program(void)
{
	static t_prog	program = {0};

	return (&program);
}

t_prog	*init_program(int scene_fd)
{
	t_prog	*program;
	void	*mlx_ptr;

	program = get_program();
	mlx_ptr = mlx_init();
	(void)	scene_fd; //TODO PARSE INFO INTO PROGRAM
	*program = (t_prog)
	{
		NULL,
		NULL,
		(t_light){(t_point3){0, 0, 0}, (t_color){255, 255, 0, 0}, 0},
		(t_camera){(t_point3){0, -40, 40}, normalize_vec3((t_vec3){0, 1, -1}),
		(t_vec3){0, 0, 0},
		(t_vec3){0, 0, 0}, 90, 0},
		(t_light){(t_point3){0, 0, 0}, (t_color){255, 255, 0, 0}, 0.1f},
		mlx_ptr,
		mlx_new_window(mlx_ptr, WINDOW_W, WINDOW_H, "miniRT")
	};
	return (program);
}
