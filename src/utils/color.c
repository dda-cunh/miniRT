/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/18 12:47:33 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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

int	color_to_int(t_color color)
{
	return ((color.alpha << 24 | color.red << 16 | color.green << 8
				| color.blue));
}

bool	same_color(t_color a, t_color b)
{
	return (color_to_int(a) == color_to_int(b));
}

t_color	darken_color(t_color original, double intensity)
{
	if (intensity < 0.0f)
		intensity = 0.0f;
	if (intensity > 1.0f)
		intensity = 1.0f;
	return ((t_color)
		{
			original.alpha,
			original.red - original.red * intensity,
			original.green - original.green * intensity,
			original.blue - original.blue * intensity
		});
}

t_color	brightness(t_color original, double intensity)
{
	int	result[3];

	if (intensity < 0.0f)
		intensity = 0.0f;
	if (intensity > 1.0f)
		intensity = 1.0f;
	result[0] = original.red + COLOR_WHITE.red * intensity;
	result[1] = original.green + COLOR_WHITE.green * intensity;
	result[2] = original.blue + COLOR_WHITE.blue * intensity;
	if (result[0] > 255)
		result[0] = 255;
	if (result[1] > 255)
		result[1] = 255;
	if (result[2] > 255)
		result[2] = 255;
	return ((t_color)
		{
			original.alpha,
			result[0],
			result[1],
			result[2]
		});
}
