/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:43:18 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/25 15:53:46 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/// @brief This function checks if the given string is well formated
/// as a coordinate.
/// @param coord 
/// @return 
bool	validate_fractional_value(char *coord)
{
	if (coord && *coord != '-' && !ft_isdigit(*coord))
		return (false);
	if (coord && *coord == '-')
		coord++;
	return (check_double_var(coord));
}

/// @brief This function checks if the rgb and the coordinates
/// are well formated.
/// @param rgb 
/// @param coords 
/// @return 
t_exit_status	check_coords_rgb(char **rgb, char **coords)
{
	if (!check_coordinates(coords))
		return (BAD_COORDS_FORMAT);
	if (!check_rgb_format(rgb))
		return (BAD_RGB_FORMAT);
	return (CHECK_SUCCESS);
}

t_exit_status	check_vec_orientation(char **vec_orien)
{
	int		i;
	double	orientation;

	i = 0;
	if (null_terminated_matrix_len((void *)vec_orien) != 3)
		return (WRONG_INFO_AMOUNT);
	while (vec_orien[i])
	{
		if (!validate_fractional_value(vec_orien[i]))
			return (BAD_VEC_FORMAT);
		orientation = ft_atof(vec_orien[i]);
		if (orientation < MIN_VECT || orientation > MAX_VECT)
			return (VEC_OUT_OF_RANGE);
		i++;
	}
	return (CHECK_SUCCESS);
}
