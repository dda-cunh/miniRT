/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:16:25 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/14 12:40:23 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	mini_rt(t_prog *program)
{
	t_image	buffer;

	for (int i = -7; i <= 7; i++)																					//testing
	{																												//testing
		t_collidable_shape	*sp = (t_collidable_shape *)malloc(sizeof(t_collidable_shape));							//testing
		sp->sp = (t_object_sphere){(t_point3){i * 5, i * 5, 0}, (t_color){255, 255 - abs(i) * 20 , 0, 0}, 12};		//testing
		ft_lstadd_back(&(program->collidables), ft_lstnew(new_collidable_entity(sp, ID_SPHERE)));					//testing
	}																												//testing
	t_collidable_shape	*pl = (t_collidable_shape *)malloc(sizeof(t_collidable_shape));								//testing
	pl->pl = (t_object_plane){(t_point3){0 , 0 , 0}, (t_color){255, 0, 255, 0}, (t_vec3){1 , 1 , 0.5}};				//testing
	ft_lstadd_back(&(program->collidables), ft_lstnew(new_collidable_entity(pl, ID_PLANE)));						//testing
	t_collidable_shape	*cy = (t_collidable_shape *)malloc(sizeof(t_collidable_shape));								//testing
	cy->cy = (t_object_cylinder){(t_point3){0, 5, 10}, (t_color){255, 0, 0, 255}, (t_vec3){1, 0, 0}, 8, 20};				//testing
	ft_lstadd_back(&(program->collidables), ft_lstnew(new_collidable_entity(cy, ID_CYLINDER)));						//testing
	buffer = do_rays(program);
	dump_image_window(buffer);
	mlx_hook(program->win_ptr, 2, 1L << 0, key_hook, program);
	mlx_hook(program->win_ptr, 17, 1L << 17, kill_x, program);
	mlx_loop(program->mlx_ptr);
	return (killprogram(0, program));
}

/*
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	!raytrace -> ambient lighting -> direct lighting -> shadows!
	!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
	return (mini_rt(program));
}
