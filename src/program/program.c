/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:51:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/20 14:23:19 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Function to handle a gracefull exit of the program.
 * 
 * @param keycode	The key code that triggered the program termination.
 * @param program	Pointer to the program structure.
 */
int	killprogram(int keycode, t_prog *program)
{
	if (program)
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
	}
	exit(__on_exit(keycode, NULL));
}

/**
 * Function to get the program structure.
 * 
 * @return	Pointer to the static program structure.
 */
t_prog	*get_program(void)
{
	static t_prog	program = {0};

	return (&program);
}
