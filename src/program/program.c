/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:51:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/30 10:56:41 by dda-cunh         ###   ########.fr       */
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
