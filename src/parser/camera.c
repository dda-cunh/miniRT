/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:24:04 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/25 15:53:17 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/// @brief This function checks the camera's field of view.
/// @param fov 
/// @return 
static bool	check_fov(char *fov, int min, int max)
{
	int	i_fov;

	if (!only_digits(fov))
		return (false);
	i_fov = ft_atoi(fov);
	if (ft_strlen(fov) > 3 || i_fov < min || i_fov > max)
		return (false);
	return (true);
}

/// @brief This function transforms an array to a t_vec3.
/// @param array 
/// @return 
t_vec3	array_to_vec3(char **array)
{
	double	x;
	double	y;
	double	z;

	x = ft_atof(array[0]);
	y = ft_atof(array[1]);
	z = ft_atof(array[2]);
	return ((t_vec3){x, y, z});
}

/// @brief This function sets the camera variables.
/// @param cam 
/// @param fov 
/// @param coords 
/// @param vec_orien 
static void	set_camera(t_camera *cam, char *fov, char **coords,
			char **vec_orien)
{
	cam->is_already_in_use = true;
	cam->fov = ft_atof(fov);
	cam->coords.x = ft_atof(coords[0]);
	cam->coords.y = ft_atof(coords[1]);
	cam->coords.z = ft_atof(coords[2]);
	cam->forward = normalize_vec3(array_to_vec3(vec_orien));
	cam->right = normalize_vec3(vec3_cross_product(cam->forward,
				(t_vec3){0.0f, 1.0f, 0.0f}));
	cam->up = normalize_vec3(vec3_cross_product(cam->right, cam->forward));
	cam->tan_fov = tanf(cam->fov * 0.5f * (M_PI / (180.0f + 0.001f)));
}

/// @brief This function checks if the camera informations
/// are well formated and if so it set.
/// @param fov 
/// @param coords 
/// @param vec_orien 
/// @return 
static t_exit_status	generic_camera_builder(char *fov, char **coords,
				char **vec_orien)
{
	t_exit_status	res;

	if (!fov || !coords || !vec_orien)
		return (EXIT_MALLOC);
	if (!check_fov(fov, FOV_MIN, FOV_MAX))
		return (FOV_OUT_OF_RANGE);
	if (!check_coordinates(coords))
		return (BAD_COORDS_FORMAT);
	res = check_vec_orientation(vec_orien);
	if (res == CHECK_SUCCESS)
		set_camera(&get_program()->camera, fov, coords, vec_orien);
	return (res);
}

/// @brief This function promotes a serie of checks and builds
/// the camera struct if each verification succeed.
/// @param array 
/// @return 
t_exit_status	build_camera(char **array)
{
	char			**coords;
	char			**vector_orientations;
	t_exit_status	res;

	if (get_program()->camera.is_already_in_use)
		return (OBJECT_ALREADY_IN_USE);
	if (null_terminated_matrix_len((void *)array) != 4)
		return (WRONG_INFO_AMOUNT);
	if (!check_vec_string_format(array[2], 0))
		return (BAD_VEC_FORMAT);
	coords = ft_split(array[1], ',');
	vector_orientations = ft_split(array[2], ',');
	res = generic_camera_builder(array[3], coords, vector_orientations);
	free_matrix((void **)coords, null_terminated_matrix_len((void *)coords));
	free_matrix((void **)vector_orientations,
		null_terminated_matrix_len((void *)vector_orientations));
	return (res);
}
