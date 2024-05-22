/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 19:27:49 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/display.h"


static int	clamp_channel(int channel)
{
	if (channel < 0)
		return (0);
	if (channel > 255)
		return (255);
	return (channel);
}

/**
 * @brief Clamps the channels of a t_color to the range [0, 255].
 * 
 * @param c	The color to clamp.
 * @return	The clamped color.
 */
t_color	clamp_color(t_color c)
{
	return ((t_color)
		{
			clamp_channel(c.alpha),
			clamp_channel(c.red),
			clamp_channel(c.green),
			clamp_channel(c.blue)
		});
}

/**
 * @brief Converts a packed integer representation of a ARGB color
 			to a t_color struct.
 * 
 * @param packed	The packed integer representation of the color.
 * @return			The converted t_color struct.
 */
t_color	int_to_color(int packed)
{
	return ((t_color)
		{
			(packed >> 24) & 0xFF,
			(packed >> 16) & 0xFF,
			(packed >> 8) & 0xFF,
			(packed) & 0xFF
		});
}

/**
 * @brief Converts a t_color(ARGB) struct to a packed integer representation.
 * 
 * @param color	The t_color struct to convert.
 * @return		The packed integer representation of the color.
 */
int	color_to_int(t_color color)
{
	return ((color.alpha << 24 | color.red << 16 | color.green << 8
			| color.blue));
}

/**
 * @brief Checks if two ARGB colors are the same.
 * 
 * @param a	The first color.
 * @param b	The second color.
 * @return	1 if the colors are the same, 0 otherwise.
 */
int	same_color(t_color a, t_color b)
{
	return (color_to_int(a) == color_to_int(b));
}
