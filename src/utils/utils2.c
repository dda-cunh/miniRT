/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:39:57 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/17 22:49:31 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/// @brief This function counts how many elements are in the array.
/// @param array 
/// @return 
size_t	array_len(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
		i++;
	return (i);
}

/// @brief This function displays a customized
/// check message given the exit_status.
/// @param code 
void	check_msg(t_exit_status code)
{
	if (code == EXIT_MISSING_OBJ)
		ft_putstr_fd("Missing object:\t", STD_OUT);
	else if (code == EXIT_GOOD)
		ft_putstr_fd("Clean exit", STD_ERR);
	else if (code == INVALID_OBJECT)
		ft_putstr_fd("Invalid object", STD_ERR);
	else if (code == OBJECT_ALREADY_IN_USE)
		ft_putstr_fd("Object already set", STD_ERR);
	else if (code == WRONG_INFO_AMOUNT)
		ft_putstr_fd("Wrong amount of informations", STD_ERR);
	else if (code == BAD_RGB_FORMAT)
		ft_putstr_fd("Invalid RGB format", STD_ERR);
	else if (code == BAD_COORDS_FORMAT)
		ft_putstr_fd("Invalid coordinates format", STD_ERR);
	else if (code == BAD_RATIO_RANGE)
		ft_putstr_fd("Invalid ratio range", STD_ERR);
	else
		check_msg2(code);
}

/// @brief This function displays a customized
/// check message given the exit_status, extension.
void	check_msg2(t_exit_status code)
{
	if (code == FOV_OUT_OF_RANGE)
		ft_putstr_fd("Field Of View out of range", STD_ERR);
	else if (code == VEC_OUT_OF_RANGE)
		ft_putstr_fd("Vector magnitude out of range", STD_ERR);
	else if (code == INVALID_SPHERE_DIAMETER)
		ft_putstr_fd("Invalid sphere diameter", STD_ERR);
	else if (code == INVALID_CYLINDER_DIAMETER)
		ft_putstr_fd("Invalid cylinder diameter", STD_ERR);
	else if (code == INVALID_CYLINDER_HEIGHT)
		ft_putstr_fd("Invalid cylinder height", STD_ERR);
	else if (code == INVALID_RATIO_FORMAT)
		ft_putstr_fd("Invalid ratio format", STD_ERR);
	else if (code == BAD_VEC_FORMAT)
		ft_putstr_fd("Invalid vector format", STD_ERR);
}

/// @brief This function checks if the string, which represents
/// the rgb is well formated.
/// @param rgb 
/// @param nums_counter 
/// @return 
bool	check_rgb_string_format(char *rgb, int nums_counter)
{
	int	counter;

	counter = 0;
	while (rgb && ft_isdigit(*rgb))
	{
		rgb++;
		counter++;
	}
	if (rgb && *rgb && *rgb == ',' && counter <= 3 && nums_counter != 2)
		return (check_rgb_string_format(++rgb, ++nums_counter));
	else if (rgb && !*rgb && counter <= 3 && nums_counter == 2)
		return (true);
	return (false);
}

/// @brief This function checks if the string, which represents
/// the vec is well formated.
/// @param vec 
/// @param nums_counter 
/// @return 
bool	check_vec_string_format(char *vec, int nums_counter)
{
	int		counter;

	counter = 0;
	if (vec && *vec == '-' && ft_isdigit(*(vec + 1)))
		vec++;
	while (vec && (ft_isdigit(*vec) || *vec == '.'))
		vec++;
		counter++;
	if (vec && *vec && *vec == ',' && counter <= 3 && nums_counter != 2)
		return (check_vec_string_format(++vec, ++nums_counter));
	else if (vec && !*vec && counter <= 3 && nums_counter == 2)
		return (true);
	return (false);
}
