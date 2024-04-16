/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:16:25 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/04/16 16:36:28 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	render(t_prog *program)
{
	do_rays(program);
	trace(program);
	ft_putendl_fd("Finished rendering", STD_OUT);
	mlx_hook(program->win_ptr, 2, 1L << 0, key_hook, program);
	mlx_hook(program->win_ptr, 17, 1L << 17, kill_x, program);
	mlx_loop(program->mlx_ptr);
	return (killprogram(EXIT_GOOD, program));
}

int	main(int ac, char **av)
{
	t_prog	*program;

	if (ac != 2)
		return (killprogram(EXIT_ARGC, NULL));
	parser(av[1]);
	program = get_program();
	program->mlx_ptr = mlx_init();
	program->win_ptr = mlx_new_window(program->mlx_ptr,
			WINDOW_W, WINDOW_H, "miniRT");
	if (!program->mlx_ptr || !program->win_ptr)
		return (killprogram(EXIT_MLX, program));
	return (render(program));
}
