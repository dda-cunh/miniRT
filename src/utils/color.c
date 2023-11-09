/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/11/03 17:54:48 by dda-cunh         ###   ########.fr       */
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

t_color	get_pixel_color(t_image image, int x, int y)
{
	char	*img_data;
	int		color;

	img_data = mlx_get_data_addr(image.ptr, &image.bpp,
			&image.line_len, &image.endian);
	color = *(int *)(img_data + (y * image.line_len + x * (image.bpp / 8)));
	return (int_to_color(color));
}
