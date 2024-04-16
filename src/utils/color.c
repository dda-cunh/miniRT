/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/30 16:08:33 by dda-cunh         ###   ########.fr       */
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

t_color	append_colors(t_color a, double b_intensity, t_color b)
{
	return ((t_color)
		{
			a.alpha,
			fmin(255, a.red + b_intensity * b.red * 0.2),
			fmin(255, a.green + b_intensity * b.green * 0.2),
			fmin(255, a.blue + b_intensity * b.blue * 0.2)
		});
}

t_color	blend_colors(t_color original, double intensity, t_color to_apply)
{
	double	intensity_orig;
	short	result[3];

	if (intensity < 0.0f)
		intensity = 0.0f;
	if (intensity > 1.0f)
		intensity = 1.0f;
	intensity_orig = 1 - intensity;
	result[0] = original.red * intensity_orig + to_apply.red * intensity;
	result[1] = original.green * intensity_orig + to_apply.green * intensity;
	result[2] = original.blue * intensity_orig + to_apply.blue * intensity;
	return ((t_color)
		{
			original.alpha,
			fmin(255, result[0]),
			fmin(255, result[1]),
			fmin(255, result[2])
		});
}
