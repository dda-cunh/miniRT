/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/18 17:35:44 by dda-cunh         ###   ########.fr       */
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

int	argb_to_int(t_byte alpha, t_byte red, t_byte green, t_byte blue)
{
	return ((alpha << 24 | red << 16 | green << 8 | blue));
}

t_color	sum_colors(t_color color1, t_color color2)
{
	int	sum;

	sum = argb_to_int(color1.alpha, color1.red, color1.blue, color1.blue)
			+ argb_to_int(color2.alpha, color2.red, color2.blue, color2.blue);
	return (int_to_color(sum));
}

