/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:22:10 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/06 14:58:17 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_image	new_image(int w, int h, t_prog window)
{
	t_image	image;

	image.win = window;
	image.ptr = mlx_new_image(window.mlx_ptr, w, h);
	image.addr = mlx_get_data_addr(image.ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
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
