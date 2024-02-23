/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:44:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/23 15:36:18 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	_add(t_cvector *self, void *content)
{
	unsigned char	*content_bytes;

	if (!self || !content)
		return ;
	if (self->length + 1 >= self->capacity)
		self->array = ft_realloc(self->array, self->capacity * CVECTOR_SCALE);
	content_bytes = (unsigned char *)content;
	ft_memmove(self->array + (self->length * self->type_size),
			content_bytes, self->type_size);
	self->length += 1;
}

static void	_set(t_cvector *self, size_t index, void *content)
{
	unsigned char	*content_bytes;

	if (!self)
		return ;
	if (index >= self->capacity)
		return ;
	content_bytes = (unsigned char *)content;
	ft_memmove(self->array + (index * self->type_size),
			content_bytes, self->type_size);
}

static unsigned char	*_get(t_cvector *self, size_t index)
{
	if (!self || index >= self->capacity)
		return (NULL);
	return (self->array + (index * self->type_size));
}

static void	_destroy(t_cvector *self)
{
	size_t	i;

	if (self)
	{
		if (self->array)
		{
			if (self->elem_destroy)
			{
				i = 0;
				while (i < self->length)
					self->elem_destroy(self->get(self, i++));
			}
			free(self->array);
		}
		free(self);
	}
}

t_cvector	*cvector_new(size_t type_size, void (*elem_destroy)(void *))
{
	t_cvector   *vector;

	vector = malloc(sizeof(t_cvector));
	if (!vector)
		return (NULL);
	vector->array = malloc(type_size * CVECTOR_INIT_CAP);
	if (!vector->array)
	{
		free(vector);
		return (NULL);
	}
	vector->capacity = CVECTOR_INIT_CAP;
	vector->type_size = type_size;
	vector->length = 0;
	vector->get = _get;
	vector->set = _set;
	vector->add = _add;
	vector->destroy = _destroy;
	vector->elem_destroy = elem_destroy;
	return (vector);
}
