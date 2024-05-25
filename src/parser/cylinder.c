/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:02:12 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/25 15:55:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_exit_status	check_cylinder_diameter_height(char *diameter, char *height)
{
	if (!check_double_var(diameter) || ft_strlen(diameter) > 10)
		return (INVALID_CYLINDER_DIAMETER);
	if (!check_double_var(height) || ft_strlen(height) > 10)
		return (INVALID_CYLINDER_HEIGHT);
	return (CHECK_SUCCESS);
}

t_exit_status	create_cylinder(t_object_cylinder cy)
{
	t_object_cylinder	*cy_ptr;
	t_cvector			*collidables;

	cy_ptr = new_cylinder(cy);
	if (!cy_ptr)
		return (EXIT_MALLOC);
	collidables = get_program()->collidables;
	collidables->add(collidables, new_collidable_shape(cy_ptr), true);
	return (CHECK_SUCCESS);
}

t_exit_status	set_cylinder(char **array, char **coords,
				char **vec, char **rgb)
{
	t_object_cylinder	cy;

	cy._id = ID_CYLINDER;
	cy.center.x = ft_atof(coords[0]);
	cy.center.y = ft_atof(coords[1]);
	cy.center.z = ft_atof(coords[2]);
	cy.color.alpha = 255;
	cy.color.red = ft_atoi(rgb[0]);
	cy.color.green = ft_atoi(rgb[1]);
	cy.color.blue = ft_atoi(rgb[2]);
	cy.axis.x = ft_atof(vec[0]);
	cy.axis.y = ft_atof(vec[1]);
	cy.axis.z = ft_atof(vec[2]);
	cy.diameter = ft_atof(array[3]);
	cy.height = ft_atof(array[4]);
	return (create_cylinder(cy));
}

t_exit_status	build_cylinder(char **array)
{
	char			**rgb;
	char			**coords;
	char			**vec;
	t_exit_status	res;

	if (null_terminated_matrix_len((void *)array) != 6)
		return (WRONG_INFO_AMOUNT);
	if (!check_rgb_string_format(array[5], 0))
		return (BAD_RGB_FORMAT);
	if (!check_vec_string_format(array[2], 0))
		return (BAD_VEC_FORMAT);
	coords = ft_split(array[1], ',');
	vec = ft_split(array[2], ',');
	rgb = ft_split(array[5], ',');
	res = check_coords_vec_rgb(coords, vec, rgb);
	if (res == CHECK_SUCCESS)
		res = check_cylinder_diameter_height(array[3], array[4]);
	if (res == CHECK_SUCCESS)
		res = set_cylinder(array, coords, vec, rgb);
	free_matrix((void **)coords, null_terminated_matrix_len((void *)coords));
	free_matrix((void **)vec, null_terminated_matrix_len((void *)vec));
	free_matrix((void **)rgb, null_terminated_matrix_len((void *)rgb));
	return (res);
}
