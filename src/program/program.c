/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:51:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/26 15:13:10 by arabelo-         ###   ########.fr       */
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

static t_prog	*new_program(char *title)
{
	t_prog	*program;

	program = get_program();
	program->mlx_ptr = mlx_init();
	if (!program->mlx_ptr)
		return (NULL);
	program->win_ptr = mlx_new_window(program->mlx_ptr,
		WINDOW_W, WINDOW_H, title);
	if (!program->win_ptr)
		return (NULL);
	return (program);
}

t_prog	*init_program(void)
{
	t_prog	*program;

	program = new_program("miniRT");
	if (!program)
		killprogram(EXIT_MLX, get_program());
	return (program);
}
