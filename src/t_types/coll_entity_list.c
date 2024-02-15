/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_entity_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:08:18 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/15 17:22:56 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	add_end(t_coll_entity_list **head, t_collidable_entity *ent)
{
	t_coll_entity_list	*curr_node;

	if (head)
	{
		curr_node = *head;
		if (curr_node)
		{
			while (curr_node->next)
				curr_node = curr_node->next;
			curr_node->next = coll_entity_list_new(ent);
		}
	}
}

static void	destroy(t_coll_entity_list *self)
{
	if (self)
	{
		if (self->ent)
		{
			if (self->ent->id == ID_CYLINDER)
				self->ent->object->cy->destroy(self->ent->object->cy);
			if (self->ent->id == ID_SPHERE)
				self->ent->object->sp->destroy(self->ent->object->sp);
			if (self->ent->id == ID_PLANE)
				self->ent->object->pl->destroy(self->ent->object->pl);
		}
		free(self);
	}
}

t_coll_entity_list	*coll_entity_list_new(t_collidable_entity *ent)
{
	t_coll_entity_list	*node;

	node = ft_calloc(1, sizeof(t_coll_entity_list));
	if (!node)
		return (NULL);
	node->ent = ent;
	node->next = NULL;
	node->add_end = add_end;
	node->destroy = destroy;
	return (node);
}
