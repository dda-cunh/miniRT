/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:10:15 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/25 15:55:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_exit_status	check_coords_vec_rgb(char **coords, char **vec, char **rgb)
{
	if (!coords || !vec || !rgb)
		return (EXIT_MALLOC);
	if (!check_coordinates(coords))
		return (BAD_COORDS_FORMAT);
	if (!check_rgb_format(rgb))
		return (BAD_RGB_FORMAT);
	return (check_vec_orientation(vec));
}

t_exit_status	set_plane(char **coords, char **vec, char **rgb)
{
	t_object_plane	*pl;
	t_cvector		*collidables;
	t_point3		point;
	t_color			colors;
	t_vec3			normal;

	point.x = ft_atof(coords[0]);
	point.y = ft_atof(coords[1]);
	point.z = ft_atof(coords[2]);
	colors.alpha = 255;
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
	collidables = get_program()->collidables;
	collidables->add(collidables, new_collidable_shape(pl), true);
	return (CHECK_SUCCESS);
}

t_exit_status	build_plane(char **array)
{
	char			**rgb;
	char			**coords;
	char			**vec;
	t_exit_status	res;

	if (null_terminated_matrix_len((void *)array) != 4)
		return (WRONG_INFO_AMOUNT);
	if (!check_rgb_string_format(array[3], 0))
		return (BAD_RGB_FORMAT);
	if (!check_vec_string_format(array[2], 0))
		return (BAD_VEC_FORMAT);
	coords = ft_split(array[1], ',');
	vec = ft_split(array[2], ',');
	rgb = ft_split(array[3], ',');
	res = check_coords_vec_rgb(coords, vec, rgb);
	if (res == CHECK_SUCCESS)
		res = set_plane(coords, vec, rgb);
	free_matrix((void **)coords, null_terminated_matrix_len((void *)coords));
	free_matrix((void **)vec, null_terminated_matrix_len((void *)vec));
	free_matrix((void **)rgb, null_terminated_matrix_len((void *)rgb));
	return (res);
}
