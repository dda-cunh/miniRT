/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:22:10 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 19:24:12 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/display.h"

/**
 * Creates a new image with the specified width and height.
 *
 * @param w			The width of the image.
 * @param h			The height of the image.
 * @param window	The window associated with the image.
 * @return			The newly created image.
 */
t_image	new_image(int w, int h, t_window window)
{
	t_image	image;

	image.win = window;
	image.ptr = mlx_new_image(image.win.mlx_ptr, w, h);
	image.addr = mlx_get_data_addr(image.ptr, &(image.bpp),
			&(image.line_len), &(image.endian));
	image.w = w;
	image.h = h;
	return (image);
}

/**
 * Sets the color of a pixel at the specified coordinates in the image.
 *
 * @param image	The image to set the pixel color in.
 * @param x		The x-coordinate of the pixel.
 * @param y		The y-coordinate of the pixel.
 * @param color	The color to set the pixel to.
 */
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

/**
 * Retrieves the color of a pixel at the specified coordinates in the image.
 *
 * @param image	The image to get the pixel color from.
 * @param x		The x-coordinate of the pixel.
 * @param y		The y-coordinate of the pixel.
 * @return		The color of the pixel at the specified coordinates.
 */
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

/**
 * Destroys the image after puting it onto the associated window.
 *
 * @param buffer	The image to dump onto the window.
 */
void	dump_image_window(t_image buffer)
{
	if (!buffer.win.mlx_ptr || !buffer.win.mlx_ptr)
		return ;
	mlx_put_image_to_window(buffer.win.mlx_ptr, buffer.win.win_ptr,
		buffer.ptr, 0, 0);
	mlx_destroy_image(buffer.win.mlx_ptr, buffer.ptr);
	return ;
}
