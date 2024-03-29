/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:39:57 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/27 17:28:50 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (code == INVALID_OBJECT)
		ft_putstr_fd("Invalid object:\t", STD_ERR);
	else if (code == OBJECT_ALREADY_IN_USE)
		ft_putstr_fd("Object already set:\t", STD_ERR);
	else if (code == WRONG_INFO_AMOUNT)
		ft_putstr_fd("Wrong amount of informations:\t", STD_ERR);
	else if (code == BAD_RGB_FORMAT)
		ft_putstr_fd("Invalid RGB format:\t", STD_ERR);
	else if (code == BAD_COORDS_FORMAT)
		ft_putstr_fd("Invalid coordinates format:\t", STD_ERR);
	else if (code == BAD_RATIO_RANGE)
		ft_putstr_fd("Invalid ratio range:\t", STD_ERR);
	else if (code == FOV_OUT_OF_RANGE)
		ft_putstr_fd("Field Of View out of range:\t", STD_ERR);
	else if (code == VEC_OUT_OF_RANGE)
		ft_putstr_fd("Vector magnitude out of range:\t", STD_ERR);
	else if (code == INVALID_SPHERE_DIAMETER)
		ft_putstr_fd("Invalid sphere diameter:\t", STD_ERR);
	else if (code == INVALID_CYLINDER_DIAMETER)
		ft_putstr_fd("Invalid cylinder diameter:\t", STD_ERR);
	else if (code == INVALID_CYLINDER_HEIGHT)
		ft_putstr_fd("Invalid cylinder height:\t", STD_ERR);
	else if (code == INVALID_RATIO_FORMAT)
		ft_putstr_fd("Invalid ratio format:\t", STD_ERR);
}
