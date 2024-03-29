/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:11:46 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/27 18:07:54 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_exit_status	set_sphere(char *diameter,
							char **coords, char **rgb)
{
	t_object_sphere	*sp;
	t_point3	center;
	t_color		colors;
	double		diam;

	center.x = ft_atof(coords[0]);
	center.y = ft_atof(coords[1]);
	center.z = ft_atof(coords[2]);
	colors.alpha = 0;
	colors.red = ft_atoi(rgb[0]);
	colors.green = ft_atoi(rgb[1]);
	colors.blue = ft_atoi(rgb[2]);
	diam = ft_atof(diameter);
	sp = new_sphere(center, colors, diam);
	if (!sp)
		return (EXIT_MALLOC);
	sp->_id = ID_SPHERE;
	get_program()->collidables->add(get_program()->collidables,
		new_collidable_shape(sp), true); /// NEW_COLLIDABLE_SHAPE ALLOCATES MEMORY, CHECK FOR NULL!
	return (CHECK_SUCCESS);
}

/// @brief This function checks a sphere's diameter.
/// @param diameter 
/// @return 
bool	check_sphere_diameter(char *diameter)
{
	double	diam;

	if (!check_double_var(diameter))
		return (false);
	diam = ft_atof(diameter);
	if (diam <= 0.0)
		return (false);
	return (true);
}

t_exit_status	build_sphere(char **array)
{
	t_exit_status	res;
	char			**coords;
	char			**rgb;

	if (array_len(array) != 4)
		return (WRONG_INFO_AMOUNT);
	if (!check_sphere_diameter(array[2]))
		return (INVALID_SPHERE_DIAMETER);
	coords = ft_split(array[1], ',');
	if (!coords)
		return (EXIT_MALLOC);
	rgb = ft_split(array[3], ',');
	if (!rgb)
	{
		free_matrix((void **)coords, array_len(array));
		return (EXIT_MALLOC);
	}
	res = check_coords_rgb(rgb, coords);
	if (res == CHECK_SUCCESS)
		res = set_sphere(array[2], coords, rgb);
	free_matrix((void **)coords, array_len(coords));
	free_matrix((void **)rgb, array_len(rgb));
	return (res);
}
