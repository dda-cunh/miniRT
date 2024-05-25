/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:08:57 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/25 15:54:10 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/// @brief This function checks if the given file has a valid extension.
/// @param file 
/// @return 
bool	is_file_extension_valid(char *file)
{
	if (!file)
		return (false);
	return (!ft_strncmp(file + ft_strlen(file) - 3, ".rt", 3));
}

/// @brief This function checks if the double variable
/// in ascii format is well formated.
/// @param str 
/// @return 
bool	check_double_var(char *str)
{
	int		dot_counter;
	bool	digit_before_dot;
	bool	digit_after_dot;
	bool	is_dot;

	dot_counter = 0;
	digit_after_dot = false;
	digit_before_dot = false;
	is_dot = false;
	while (str && (ft_isdigit(*str) || *str == '.'))
	{
		if (*str == '.')
		{
			is_dot = true;
			dot_counter++;
		}
		if (dot_counter > 1)
			return (false);
		if (!dot_counter)
			digit_before_dot = true;
		else if (dot_counter && digit_before_dot && ft_isdigit(*str))
			digit_after_dot = true;
		str++;
	}
	return (str && !*str && digit_before_dot && (digit_after_dot == is_dot));
}

/// @brief This function checks if the given string
/// is only made by digits.
/// @param str 
/// @return 
bool	only_digits(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

/// @brief This function checks if the given
/// rgb array is well formated.
/// @param rgb 
/// @return 
bool	check_rgb_format(char **rgb)
{
	int		i;
	int		rgb_value;

	i = 0;
	if (null_terminated_matrix_len((void *)rgb) != 3)
		return (false);
	while (rgb[i])
	{
		rgb_value = ft_atoi(rgb[i]);
		if (ft_strlen(rgb[i]) > 3 || !only_digits(rgb[i])
			|| rgb_value < 0 || rgb_value > 255)
			return (false);
		i++;
	}
	return (true);
}

/// @brief This function checks the coordinates format and range
/// @param coords 
/// @return 
bool	check_coordinates(char **coords)
{
	int		i;

	i = 0;
	if (null_terminated_matrix_len((void *)coords) != 3)
		return (false);
	while (coords[i])
	{
		if (ft_strlen(coords[i]) > 5 || !validate_fractional_value(coords[i]))
			return (false);
		i++;
	}
	return (true);
}
