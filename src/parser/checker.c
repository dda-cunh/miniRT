/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:08:57 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/30 13:03:45 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	int	dot_counter;

	dot_counter = 0;
	while (str && (ft_isdigit(*str) || *str == '.'))
	{
		if (*str == '.')
			dot_counter++;
		if (dot_counter > 1)
			return (false);
		str++;
	}
	return (str && !*str);
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
	if (array_len(rgb) != 3)
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
	if (array_len(coords) != 3)
		return (false);
	while (coords[i])
	{
		if (ft_strlen(coords[i]) > 5 || !validate_fractional_value(coords[i]))
			return (false);
		i++;
	}
	return (true);
}
