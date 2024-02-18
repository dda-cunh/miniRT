/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:54:17 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/18 14:40:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static t_coll_point3	collide(t_object_plane *self, t_ray3 ray)
{
	double	scalar;
	double	denom;

	scalar = -1;
	denom = vec3_dot_product(self->normal, ray.direction);
	if (denom > EPSILON || denom < -EPSILON)
		scalar = vec3_dot_product(vec3_sub(self->point, ray.origin),
				self->normal) / denom;
	return ((t_coll_point3)
		{
			point3_plus_vec3(ray.origin,scale_vec3(ray.direction, scalar)),
			self->color,
			self->normal,
			scalar
		});
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
	*obj = (t_object_plane){ID_PLANE, point, color, normal, destroy,
			collide};
	return (obj);
}
