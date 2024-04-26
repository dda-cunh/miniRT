/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:18:24 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/04/26 22:16:22 by dda-cunh         ###   ########.fr       */
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
	double	norm_color[3];
	double	sum;
	double	specular;
	double	diffuse;
	t_vec3	h;

	ft_bzero(norm_color, 3 * sizeof(double));
	h = vec3_sub(scale_vec3(coll.normal, 2 * vec3_dot_product(coll.normal, to_light)), to_light);
	diffuse = fmax(0, vec3_dot_product(coll.normal, to_light));
	specular = pow(vec3_dot_product(normalize_vec3(vec3_from_points(coll.coords,
				get_program()->camera.coords)), h), GLOSSINESS);
	sum = coll.coll_color.red + coll.coll_color.green + coll.coll_color.blue;
	if (sum > 0)
	{
		norm_color[0] = coll.coll_color.red / sum;
		norm_color[1] = coll.coll_color.green / sum;
		norm_color[2] = coll.coll_color.blue / sum;
	}
	return (clamp_color((t_color)
		{
			coll.coll_color.alpha,
			norm_color[0] * (ambient.color.red + diffuse)
					+ light.color.red * specular,
			norm_color[1] * (ambient.color.green + diffuse)
					+ light.color.green * specular,
			norm_color[2] * (ambient.color.blue + diffuse)
					+ light.color.blue * specular
		}));
}

