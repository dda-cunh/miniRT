/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/06 14:22:37 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_color	int_to_color(int packed)
{
	return ((t_color){packed >> 24 & 0xFF, packed >> 16 & 0xFF,
		packed >> 8 & 0xFF, packed & 0xFF});
}

int	color_to_int(t_color color)
{
	return (color.alpha << 24 | color.red << 16 | color.green << 8
		| color.blue);
}

t_color	sum_colors(t_color color1, t_color color2)
{
	int	sum;

	sum = color_to_int(color1) + color_to_int(color2);
	return (int_to_color(sum));
}

