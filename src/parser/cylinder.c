/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 22:02:12 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/30 11:14:40 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

	cy_ptr = new_cylinder(cy);
	if (!cy_ptr)
		return (EXIT_MALLOC);
	get_program()->collidables->add(get_program()->collidables,
		new_collidable_shape(cy_ptr), true);
	return (CHECK_SUCCESS);
}

t_exit_status	set_cylinder(char **array, char **coords,
				char **vec, char **rgb)
{
	t_object_cylinder	cy;
	t_point3			center;
	t_color				colors;
	t_vec3				axis;

	cy._id = ID_CYLINDER;
	cy.disk1 = NULL;
	cy.disk2 = NULL;
	center.x = ft_atof(coords[0]);
	center.y = ft_atof(coords[1]);
	center.z = ft_atof(coords[2]);
	colors.alpha = 0;
	colors.red = ft_atoi(rgb[0]);
	colors.green = ft_atoi(rgb[1]);
	colors.blue = ft_atoi(rgb[2]);
	axis.x = ft_atof(vec[0]);
	axis.y = ft_atof(vec[1]);
	axis.z = ft_atof(vec[2]);
	cy.diameter = ft_atof(array[3]);
	cy.height = ft_atof(array[4]);
	cy.radius = cy.diameter / 2;
	cy.destroy = NULL;
	cy.collide = NULL;
	return (create_cylinder(cy));
}

t_exit_status	build_cylinder(char **array)
{
	char			**rgb;
	char			**coords;
	char			**vec;
	t_exit_status	res;

	if (array_len(array) != 6)
		return (WRONG_INFO_AMOUNT);
	coords = ft_split(array[1], ',');
	vec = ft_split(array[2], ',');
	rgb = ft_split(array[5], ',');
	res = check_coords_vec_rgb(coords, vec, rgb);
	if (res == CHECK_SUCCESS)
		res = check_cylinder_diameter_height(array[3], array[4]);
	if (res == CHECK_SUCCESS)
		res = set_cylinder(array, coords, vec, rgb);
	free_matrix((void **)coords, array_len(coords));
	free_matrix((void **)vec, array_len(vec));
	free_matrix((void **)rgb, array_len(rgb));
	return (res);
}