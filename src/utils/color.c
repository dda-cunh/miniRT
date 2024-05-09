/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/09 13:07:53 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_color	clamp_color(t_color c)
{
	return ((t_color)
		{
			fmax(0, fmin(255, c.alpha)),
			fmax(0, fmin(255, c.red)),
			fmax(0, fmin(255, c.green)),
			fmax(0, fmin(255, c.blue))
		});
}

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

t_color	lighting(t_coll_point3 coll, t_vec3 to_light, t_light light,
				t_light ambient)
{
	double	channels[3];
	double	specular;
	double	diffuse;
	t_vec3	h;

	diffuse = fmax(0.0, vec3_dot_product(coll.normal, to_light));
	h = normalize_vec3(point3_plus_vec3(to_light, scale_vec3(coll.normal, -1)));
	specular = pow(fmax(0.0, vec3_dot_product(h, coll.normal)), GLOSSINESS);
	channels[0] = (ambient.color.red * (coll.coll_color.red / 255.0))
			+ light.color.red * (diffuse + specular);
	channels[1] = (ambient.color.green * (coll.coll_color.green / 255.0))
			+ light.color.green * (diffuse + specular);
	channels[2] = (ambient.color.blue * (coll.coll_color.blue / 255.0))
			+ light.color.blue * (diffuse + specular);
	return (clamp_color((t_color)
		{
			coll.coll_color.alpha,
			channels[0],
			channels[1],
			channels[2]
		}));
}
