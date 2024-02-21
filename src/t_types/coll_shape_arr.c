/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_shape_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:08:18 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/21 15:29:15 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	destroy(t_coll_shape_arr *self)
{
	t_collidable_id	id;
	int				i;

	i = -1;
	if (!self)
		return ;
	while (++i < self->length)
	{
		if (self->ent[i])
		{
			id = get_coll_shape_id(*self->ent[i]);
			if (id == ID_CYLINDER)
				self->ent[i]->cy->destroy(self->ent[i]->cy);
			if (id == ID_SPHERE)
				self->ent[i]->sp->destroy(self->ent[i]->sp);
			if (id == ID_PLANE)
				self->ent[i]->pl->destroy(self->ent[i]->pl);
		}
	}
	if (self->ent)
		free(self->ent);
	free(self);
}

t_coll_shape_arr	*coll_shape_arr_new(int length)
{
	t_coll_shape_arr	*arr;

	if (length <= 0)
		return (NULL);
	arr = ft_calloc(1, sizeof(t_coll_shape_arr));
	if (!arr)
		return (NULL);
	arr->ent = ft_calloc(length, sizeof(t_collidable_shape *));
	if (!arr->ent)
	{
		free(arr);
		return (NULL);
	}
	arr->length = length;
	arr->destroy = destroy;
	return (arr);
}
