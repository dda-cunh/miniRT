/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:16:25 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/18 12:16:53 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static void	populate_test(t_prog *program)	//TESTING
{
	program->collidables = coll_entity_list_new(NULL);
	for (int i = -4; i <= 4; i++)
	{
		t_object_sphere	*sp;
		if (i == 0)
			continue ;
		sp = new_sphere((t_point3){10, 10, 0}, COLOR_RED, 12);

		program->collidables->add_end(&program->collidables, sp);
	}
	t_object_plane	*pl = new_plane((t_point3){0 , 0 , -5}, (COLOR_GREEN), (t_vec3){0 , 0 , 1});
	program->collidables->add_end(&program->collidables, pl);
	t_object_cylinder	*cy = new_cylinder((t_object_cylinder)
				{
					ID_CYLINDER,
					NULL,
					NULL,
					(t_point3){0, 5, 10},
					COLOR_BLUE,
					normalize_vec3((t_vec3){-1, 0, 1}),
					8,
					15,
					NULL,
					NULL
				});
	program->collidables->add_end(&program->collidables, cy);
	t_light	*light = malloc(sizeof(t_light));
	*light = (t_light){(t_point3){-5, -5, 30}, COLOR_RED, 0.5f};
	program->lights = ft_lstnew(light);
}

// static void	print_collisions(t_coll_point3 **collisions)	//DEBUG
// {
// 	for (int i = 0; i < WINDOW_H; i++)
// 	{
// 		for (int j = 0; j < WINDOW_W; j++)
// 		{
// 			printf("Collision on [%d][%d]:\n{\n", i, j);
// 			printf("\tcolor: %d\n", color_to_int(collisions[i][j].color));
// 			printf("\tcoords: (%f, %f, %f)\n", collisions[i][j].coords.x
// 					, collisions[i][j].coords.y, collisions[i][j].coords.z);
// 			printf("\tscalar: %f\n}\n", collisions[i][j].scalar);
// 		}
// 	}
// }

static void	ambient(t_prog *program)
{
	t_color	new_color;
	t_image buffer;
	int		curr_x;
	int		curr_y;

	if (!program)
		return ;
	buffer = new_image(WINDOW_W, WINDOW_H, *program);
	curr_y = 0;
	while (curr_y < WINDOW_H)
	{
		curr_x = 0;
		while (curr_x < WINDOW_W)
		{
			if (program->collisions[curr_y][curr_x].scalar > EPSILON)
			{
				new_color = brightness(program->collisions[curr_y][curr_x].color,
						program->ambient_l.ratio);
				set_image_pixel(buffer, curr_x, curr_y, new_color);
				program->collisions[curr_y][curr_x].color = new_color;
			}
			curr_x++;
		}
		curr_y++;
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
	int		scene_fd;

	if (ac != 2)
		return (killprogram(EXIT_ARGC, NULL));
	if (ft_strncmp(av[1] + ft_strlen(av[1]) - 3, ".rt", 3))
		return (killprogram(EXIT_FILE_EXTENSION, NULL));
	scene_fd = open(av[1], O_RDONLY, 0777);
	if (scene_fd == -1)
		return (killprogram(EXIT_OPENING_SCENE, NULL));
	program = init_program(scene_fd);
	close(scene_fd);
	if (!program)
		return (killprogram(EXIT_MALLOC, program));
	if (!program->mlx_ptr || !program->win_ptr)
		return (killprogram(EXIT_MLX, program));
	program->camera.right = normalize_vec3(vec3_cross_product(
				program->camera.forward,
				(t_vec3){0.0f, 1.0f, 0.0f}));
	program->camera.up = vec3_cross_product(program->camera.right,
			program->camera.forward);
	program->camera.tan_fov = tanf(program->camera.fov * 0.5f
			* (M_PI / 180.0f));
	populate_test(program);	//TESTING
	return (mini_rt(program));
}
