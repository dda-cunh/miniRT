/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:42:28 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/25 15:55:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/// @brief This function checks if the light ratio is
/// between the min and the max given values.
/// @param str 
/// @param min 
/// @param max 
/// @return 
static bool	check_light_ratio(char *str, double min, double max)
{
	double	ratio;

	ratio = ft_atof(str);
	if (ratio < min || ratio > max)
		return (false);
	return (true);
}

/// @brief This function sets the given light struct with the
/// ratio, rgb and coords parameters depending of it's type.
/// @param light 
/// @param ratio 
/// @param rgb 
/// @param coords 
static void	set_light(t_light *light, char *ratio, char **rgb, char **coords)
{
	light->color.alpha = 0;
	light->ratio = ft_atof(ratio);
	light->color.red = ft_atoi(rgb[0]) * light->ratio;
	light->color.green = ft_atoi(rgb[1]) * light->ratio;
	light->color.blue = ft_atoi(rgb[2]) * light->ratio;
	light->is_already_in_use = true;
	if (coords)
	{
		light->coords.x = ft_atof(coords[0]);
		light->coords.y = ft_atof(coords[1]);
		light->coords.z = ft_atof(coords[2]);
	}
}

/// @brief This function checks if the light informations
/// are well formated and if so it set.
/// @param ratio 
/// @param rgb 
/// @param coords 
/// @return 
static t_exit_status	generic_light_builder(t_light *light, char *ratio,
						char **rgb, char **coords)
{
	if (!check_double_var(ratio))
		return (INVALID_RATIO_FORMAT);
	if (!check_light_ratio(ratio, MIN_RATIO, MAX_RATIO))
		return (BAD_RATIO_RANGE);
	if (!check_rgb_format(rgb))
		return (BAD_RGB_FORMAT);
	if (coords && !check_coordinates(coords))
		return (BAD_COORDS_FORMAT);
	set_light(light, ratio, rgb, coords);
	return (CHECK_SUCCESS);
}

/// @brief This function promotes a serie of checks and builds the
/// ambient light struct if each verification succeed.
/// @param array 
/// @return 
t_exit_status	build_ambient_light(char **array)
{
	t_exit_status	res;
	char			**rgb;

	if (get_program()->ambient_l.is_already_in_use)
		return (OBJECT_ALREADY_IN_USE);
	if (null_terminated_matrix_len((void *)array) != 3)
		return (WRONG_INFO_AMOUNT);
	if (!check_rgb_string_format(array[2], 0))
		return (BAD_RGB_FORMAT);
	rgb = ft_split(array[2], ',');
	if (!rgb)
		return (EXIT_MALLOC);
	if (!check_rgb_format(rgb))
	{
		free_matrix((void **)rgb, null_terminated_matrix_len((void *)rgb));
		return (BAD_RGB_FORMAT);
	}
	res = generic_light_builder(&get_program()->ambient_l,
			array[1], rgb, NULL);
	free_matrix((void **)rgb, null_terminated_matrix_len((void *)rgb));
	return (res);
}

/// @brief This function promotes a serie of checks and builds
/// the light struct if each verification succeed.
/// @param array 
/// @return 
t_exit_status	build_light(char **array)
{
	char			**rgb;
	char			**coords;
	t_exit_status	res;

	if (get_program()->light.is_already_in_use)
		return (OBJECT_ALREADY_IN_USE);
	if (null_terminated_matrix_len((void *)array) != 4)
		return (WRONG_INFO_AMOUNT);
	if (!check_rgb_string_format(array[3], 0))
		return (BAD_RGB_FORMAT);
	coords = ft_split(array[1], ',');
	if (!coords)
		return (EXIT_MALLOC);
	rgb = ft_split(array[3], ',');
	if (!rgb)
	{
		free_matrix((void **)coords, null_terminated_matrix_len((void *)coords));
		return (EXIT_MALLOC);
	}
	res = generic_light_builder(&get_program()->light, array[2], rgb, coords);
	free_matrix((void **)rgb, null_terminated_matrix_len((void *)rgb));
	free_matrix((void **)coords, null_terminated_matrix_len((void *)coords));
	return (res);
}
