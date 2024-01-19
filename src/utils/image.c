/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:22:10 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/19 12:21:34 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_image	new_image(int w, int h, t_prog program)
{
	t_image	image;

	image.win = program;
	image.ptr = mlx_new_image(program.mlx_ptr, w, h);
	image.addr = mlx_get_data_addr(image.ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

void	set_image_pixel(t_image image, int x, int y, t_color color)
{
	char	*pixel_addr;
	int		color_int;
	int		i;

	if (x < 0 || x >= image.w || y < 0 || y >= image.h)
		return ;
	if (same_color(get_image_pixel(image, x, y), color))
		return ;
	color_int = color_to_int(color);
	pixel_addr = image.addr + (y * image.line_len + x * (image.bpp / 8));
	i = -1;
	while (++i < (image.bpp / 8))
	{
		if (image.endian == 1)
			pixel_addr[i] = (color_int >> ((3 - i) * 8)) & 0xFF;
		else
			pixel_addr[i] = (color_int >> (i * 8)) & 0xFF;
	}
	return ;
}

t_color	get_image_pixel(t_image image, int x, int y)
{
	char	*pixel_addr;
	int		color;

	if (x < 0 || x >= image.w || y < 0 || y >= image.h)
		return ((t_color){0, 0, 0, 0});
	pixel_addr = image.addr + (y * image.line_len + x * (image.bpp / 8));
	color = *(int *)pixel_addr;
	return (int_to_color(color));
}
