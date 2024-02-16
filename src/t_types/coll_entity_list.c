/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_entity_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:08:18 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/16 16:29:03 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	add_end(t_coll_shape_list **head, void *t_object)
{
	t_coll_shape_list	*curr_node;

	if (head)
	{
		curr_node = *head;
		if (curr_node)
		{
			while (curr_node->next)
				curr_node = curr_node->next;
			curr_node->next = coll_entity_list_new(t_object);
		}
	}
}

static void	destroy(t_coll_shape_list *self)
{
	t_coll_shape_list	*next;
	t_collidable_id		id;

	while (self)
	{
		next = self->next;
		if (self->ent)
		{
			id = get_coll_shape_id(self->ent);
			if (id == ID_CYLINDER)
				self->ent->cy->destroy(self->ent->cy);
			if (id == ID_SPHERE)
				self->ent->sp->destroy(self->ent->sp);
			if (id == ID_PLANE)
				self->ent->pl->destroy(self->ent->pl);
			free(self->ent);
		}
		free(self);
		self = next;
	}
}

t_coll_shape_list	*coll_entity_list_new(void *t_object)
{
	t_coll_shape_list	*node;

	node = ft_calloc(1, sizeof(t_coll_shape_list));
	if (!node)
		return (NULL);
	node->ent = new_collidable_shape(t_object);
	node->next = NULL;
	node->add_end = add_end;
	node->destroy = destroy;
	return (node);
}
