/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:54:17 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/15 17:57:06 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static float	collide(t_object_plane *self, t_ray3 ray)
{
	float	scallar;
	float	denom;

	scallar = -1;
	denom = vec3_dot_product(self->normal, ray.direction);
	if (denom > EPSILON || denom < -EPSILON)
		scallar = vec3_dot_product(vec3_sub(self->point, ray.origin),
				self->normal) / denom;
	return (scallar);
}

static void	destroy(t_object_plane *self)
{
	if (self)
		free(self);
}

t_object_plane	*new_plane(t_point3 point, t_color color, t_vec3 normal)
{
	t_object_plane	*obj;

	obj = ft_calloc(1, sizeof(t_object_plane));
	if (!obj)
		return (NULL);
	*obj = (t_object_plane){point, color, normal, destroy, collide};
	return (obj);
}
