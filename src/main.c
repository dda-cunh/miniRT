/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:16:25 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 18:01:55 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	render(t_prog *program)
{
	do_rays(program);
	trace(program);
	ft_putendl_fd("Finished rendering", STD_OUT);
	mlx_hook(program->win.win_ptr, 2, 1L << 0, key_hook, program);
	mlx_hook(program->win.win_ptr, 17, 1L << 17, kill_x, program);
	mlx_loop(program->win.mlx_ptr);
	return (killprogram(EXIT_GOOD, program));
}

int	main(int ac, char **av)
{
	t_prog	*program;

	if (ac != 2)
		return (killprogram(EXIT_ARGC, NULL));
	parser(av[1]);
	program = get_program();
	program->win.mlx_ptr = mlx_init();
	program->win.win_ptr = mlx_new_window(program->win.mlx_ptr,
			WINDOW_W, WINDOW_H, "miniRT");
	if (!program->win.mlx_ptr || !program->win.win_ptr)
		return (killprogram(EXIT_MLX, program));
	return (render(program));
}
