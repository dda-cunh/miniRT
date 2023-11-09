/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:51:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/11/03 16:14:26 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	killprogram(int keycode, t_prog *program)
{
	if (program)
	{
		if (program->map.lines)
			free_2d(program->map.lines);
		if (program->mapold.lines)
			free_2d(program->mapold.lines);
		if (program->win_ptr)
			mlx_destroy_window(program->mlx_ptr, program->win_ptr);
		if (program->mlx_ptr)
		{
			mlx_loop_end(program->mlx_ptr);
			mlx_destroy_display(program->mlx_ptr);
			free(program->mlx_ptr);
		}
	}
	exit(exit_(keycode));
}

t_prog	*new_program(char *title)
{
	t_prog	*program;
	void	*mlx_ptr;

	program = malloc(sizeof(t_prog));
	if (!program)
		return (NULL);
	mlx_ptr = mlx_init();
	*program = (t_prog){(t_map){NULL, 0, 0, 0, 0}, (t_map){NULL, 0, 0, 0, 0},
		mlx_ptr, mlx_new_window(mlx_ptr, WINDOW_W, WINDOW_H, title), 0};
	return (program);
}
