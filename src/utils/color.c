/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/11 13:29:05 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * @brief Clamps the channels of a t_color to the range [0, 255].
 * 
 * @param c	The color to clamp.
 * @return	The clamped color.
 */
static t_color	clamp_color(t_color c)
{
	return ((t_color)
		{
			clamp_value(c.alpha, 0, 255),
			clamp_value(c.red, 0, 255),
			clamp_value(c.green, 0, 255),
			clamp_value(c.blue, 0, 255)
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
 * @return	true if the colors are the same, false otherwise.
 */
bool	same_color(t_color a, t_color b)
{
	return (color_to_int(a) == color_to_int(b));
}

/**
 * @brief Calculates the shading at a collision point.
 * 
 * @param coll		The collision point.
 * @param to_light	The vector from the collision point to the light source.
 * @param light		The light source.
 * @return			The shading at the collision point.
 */
t_color	lighting(t_coll_point3 coll, t_vec3 to_light, t_light light)
{
	double	channels[3];
	double	specular;
	double	diffuse;
	t_vec3	h;

	diffuse = fmax(0.0, vec3_dot_product(coll.normal, to_light));
	h = normalize_vec3(point3_plus_vec3(to_light, scale_vec3(coll.normal, -1)));
	specular = pow(fmax(0.0, vec3_dot_product(h, coll.normal)), GLOSSINESS);
	channels[0] = coll.visible_color.red
		+ light.color.red * (diffuse + specular);
	channels[1] = coll.visible_color.green
		+ light.color.green * (diffuse + specular);
	channels[2] = coll.visible_color.blue
		+ light.color.blue * (diffuse + specular);
	return (clamp_color((t_color)
			{
				coll.coll_color.alpha,
				channels[0],
				channels[1],
				channels[2]
			}));
}
