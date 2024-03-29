/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:10:15 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/27 18:20:24 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_exit_status	check_coords_vec_rgb(char **coords, char **vec, char **rgb)
{
	t_exit_status	res;

	if (!coords || !vec || !rgb)
		return (EXIT_MALLOC);
	if (!check_coordinates(coords))
		return (BAD_COORDS_FORMAT);
	if (!check_rgb_format(rgb))
		return (BAD_RGB_FORMAT);
	res = check_vec_orientation(vec);
	return (res);
}

t_exit_status	set_plane(char **coords, char **vec, char **rgb)
{
	t_object_plane	*pl;
	t_point3		point;
	t_color			colors;
	t_vec3			normal;

	point.x = ft_atof(coords[0]);
	point.y = ft_atof(coords[1]);
	point.z = ft_atof(coords[2]);
	colors.alpha = 0;
	colors.red = ft_atoi(rgb[0]);
	colors.green = ft_atoi(rgb[1]);
	colors.blue = ft_atoi(rgb[2]);
	normal.x = ft_atof(vec[0]);
	normal.y = ft_atof(vec[1]);
	normal.z = ft_atof(vec[2]);
	pl = new_plane(point, colors, normal);
	if (!pl)
		return (EXIT_MALLOC);
	pl->_id = ID_PLANE;
	get_program()->collidables->add(get_program()->collidables,
		new_collidable_shape(pl), true); /// NEW_COLLIDABLE_SHAPE ALLOCATES MEMORY, CHECK FOR NULL!
	return (CHECK_SUCCESS);
}

t_exit_status	build_plane(char **array)
{
	char			**rgb;
	char			**coords;
	char			**vec;
	t_exit_status	res;

	if (array_len(array) != 4)
		return (WRONG_INFO_AMOUNT);
	coords = ft_split(array[1], ',');
	vec = ft_split(array[2], ',');
	rgb = ft_split(array[3], ',');
	res = check_coords_vec_rgb(coords, vec, rgb);
	if (res == CHECK_SUCCESS)
		res = set_plane(coords, vec, rgb);
	free_matrix((void **)coords, array_len(coords));
	free_matrix((void **)vec, array_len(vec));
	free_matrix((void **)rgb, array_len(rgb));
	return (res);
}
