/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:16:25 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/27 18:27:23 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

// static void	populate_test(t_prog *program)	//TESTING
// {
// 	program->collidables = cvector_new(sizeof(t_collidable_shape),
// 			destroy_collidable_shape);
// 	for (int i = -4; i <= 4; i++)
// 	{
// 		t_object_sphere	*sp;
// 		if (i == 0)
// 			continue ;
// 		if (i % 2 == 0)
// 			sp = new_sphere((t_point3){i * 6, i * 6, 0}, (t_color){255, 255, 0, 0}, 15);
// 		else
// 			sp = new_sphere((t_point3){i * 6, -i * 6, 0}, (t_color){255, 255, 0, 0}, 15);
// 		program->collidables->add(program->collidables, new_collidable_shape(sp), true);
// 	}
// 	t_object_plane	*pl = new_plane((t_point3){0 , 0 , 0}, (t_color){255, 0, 255, 0}, (t_vec3){0 , 0 , 1});
// 	program->collidables->add(program->collidables, new_collidable_shape(pl), true);
// 	t_object_cylinder	*cy = new_cylinder((t_object_cylinder)
// 				{
// 					ID_CYLINDER,
// 					NULL,
// 					NULL,
// 					(t_point3){0, 5, 20},
// 					(t_color){255, 0, 0, 255},
// 					normalize_vec3((t_vec3){-1, 0, 1}),
// 					15,
// 					25,
// 					0,
// 					NULL,
// 					NULL
// 				});
// 	program->collidables->add(program->collidables, new_collidable_shape(cy), true);
// 	program->light = (t_light){(t_point3){10, -5, 40}, (t_color){255, 255, 0, 0}, 0.2f};
// }

static void	ambient(t_prog *program)
{
	t_coll_point3	*coll;
	t_image			buffer;
	int				curr_x;
	int				curr_y;

	if (!program)
		return ;
	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	curr_y = -1;
	while (++curr_y < WINDOW_H)
	{
		curr_x = -1;
		while (++curr_x < WINDOW_W)
		{
			coll = &program->collisions[curr_y][curr_x];
			if (valid_collision(coll->scalar))
			{
				coll->color = blend_colors(coll->color,
						program->ambient_l.ratio, program->ambient_l.color);
				set_image_pixel(buffer, curr_x, curr_y, coll->color);
			}
		}
	}
	dump_image_window(buffer);
}

static int	mini_rt(t_prog *program)
{
	program->collisions = do_rays(program);
	ambient(program);
	trace(program);
	mlx_hook(program->win_ptr, 2, 1L << 0, key_hook, program);
	mlx_hook(program->win_ptr, 17, 1L << 17, kill_x, program);
	mlx_loop(program->mlx_ptr);
	return (killprogram(EXIT_GOOD, program));
}

/*
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!collisions -> ambient lighting -> direct lighting -> shadows!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
int	main(int ac, char **av)
{
	t_prog	*program;
	// int		scene_fd;

	if (ac != 2)
		return (killprogram(EXIT_ARGC, NULL));
	parser(av[1]);
	// killprogram(EXIT_GOOD, get_program());
	program = init_program();
	// killprogram(EXIT_GOOD, get_program());
	// program->camera.right = normalize_vec3(vec3_cross_product(
	// 			program->camera.forward,
	// 			(t_vec3){0.0f, 1.0f, 0.0f}));
	// program->camera.up = vec3_cross_product(program->camera.right,
	// 		program->camera.forward);
	// program->camera.tan_fov = tanf(program->camera.fov * 0.5f
	// 		* (M_PI / 180.0f));
	// populate_test(program); //TESTING
	return (mini_rt(program));
}
