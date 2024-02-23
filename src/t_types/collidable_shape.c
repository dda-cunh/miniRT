/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collidable_shape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:51:55 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/23 15:30:18 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_collidable_id	get_coll_shape_id(t_collidable_shape ent)
{
	t_collidable_id	id;

	id = 0;
	if (ent.cy)
		ft_memcpy(&id, ent.cy, sizeof(t_collidable_id));
	return (id);
}

void	destroy_collidable_shape(void *shape)
{
	t_collidable_shape	*obj;
	int					id;

	obj = shape;
	if (obj)
	{
		id = get_coll_shape_id(*obj);
		if (id == ID_CYLINDER)
			return (obj->cy->destroy(obj->cy));
		else if (id == ID_SPHERE)
			return (obj->sp->destroy(obj->sp));
		else if (id == ID_PLANE)
			return (obj->pl->destroy(obj->pl));
		free(obj);
	}
}

t_collidable_shape	*new_collidable_shape(void *t_object)
{
	t_collidable_shape	*instance;
	t_collidable_id		id;

	if (!t_object)
		return (NULL);
	instance = ft_calloc(1, sizeof(t_collidable_shape));
	if (!instance)
		return (NULL);
	id = 0;
	ft_memcpy(&id, t_object, sizeof(t_collidable_id));
	if (id == ID_CYLINDER)
		instance->cy = (t_object_cylinder *) t_object;
	else if (id == ID_SPHERE)
		instance->sp = (t_object_sphere *) t_object;
	else if (id == ID_PLANE)
		instance->pl = (t_object_plane *) t_object;
	else
	{
		free(instance);
		return (NULL);
	}
	return (instance);
}
