/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:07:53 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/25 16:23:58 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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
	int	counter;

	counter = 0;
	if (vec && *vec == '-' && ft_isdigit(*(vec + 1)))
		vec++;
	while (vec && (ft_isdigit(*vec) || *vec == '.'))
	{
		vec++;
		counter++;
	}
	if (vec && *vec && *vec == ',' && counter <= 3 && nums_counter != 2)
		return (check_vec_string_format(++vec, ++nums_counter));
	else if (vec && !*vec && counter <= 3 && nums_counter == 2)
		return (true);
	return (false);
}

static void	print_exit_msg(t_exit_status exit_code, char *verbose)
{
	static char	*exit_msgs[__LEN_EXIT_ENUM] = {"", "Failed Malloc",
		"Wrong number of parameters", "Wrong file extension", "Failure at open",
		"Close failed", "Bad Scene", "MLX failed", "Missing object",
		"Invalid object", "Object already set", "Wrong amount of informations",
		"Invalid RGB format", "Invalid coordinates format",
		"Invalid ratio range", "Field Of View out of range",
		"Vector magnitude out of range", "Invalid sphere diameter",
		"Invalid cylinder diameter", "Invalid cylinder height",
		"Invalid ratio format", "Invalid vector format",
		"There's nothing to render"};

	if (exit_code < 0 || exit_code >= __LEN_EXIT_ENUM)
		return ;
	ft_putstr_fd(exit_msgs[exit_code], STD_ERR);
	if (verbose)
	{
		ft_putstr_fd(":\t", STD_ERR);
		ft_putstr_fd(verbose, STD_ERR);
	}
	ft_putchar_fd('\n', STD_ERR);
}

t_exit_status	__on_exit(t_exit_status exit_code, char *verbose)
{
	if (exit_code != EXIT_GOOD)
	{
		ft_putstr_fd(BAD_EXIT, STD_ERR);
		print_exit_msg(exit_code, verbose);
	}
	return (exit_code);
}
