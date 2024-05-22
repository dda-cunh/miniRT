/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 13:44:36 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 18:45:08 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cvector.h"

/**
 * @brief Adds an element to the dynamic array.
 *
 * @param self		The dynamic array.
 * @param content	The content to be added.
 * @param del_heap	Whether to free the memory of the content after adding.
 */
static void	_add(t_cvector *self, void *content, int del_heap)
{
	unsigned char	*content_bytes;

	if (!self || !content)
		return ;
	if (self->length >= self->capacity)
	{
		self->array = _realloc(self->array, self->capacity * self->type_size,
				self->capacity * self->type_size * CVECTOR_SCALE);
		self->capacity *= CVECTOR_SCALE;
	}
	content_bytes = (unsigned char *)content;
	_memmove(self->array + (self->length * self->type_size),
		content_bytes, self->type_size);
	if (del_heap)
		free(content);
	self->length++;
}

/**
 * @brief Sets the value of an element at a specific index in the dynamic array.
 *
 * @param self		The dynamic array.
 * @param index		The index of the element to be set.
 * @param content	The content to be set.
 * @param del_heap	Whether to free the memory of the content after setting.
 */
static void	_set(t_cvector *self, size_t index, void *content, int del_heap)
{
	unsigned char	*content_bytes;

	if (!self)
		return ;
	if (index >= self->capacity)
		return ;
	content_bytes = (unsigned char *)content;
	_memmove(self->array + (index * self->type_size),
		content_bytes, self->type_size);
	if (del_heap)
		free(content);
}

/**
 * @brief Retrieves the value of an element at a specific index in the
 			dynamic array.
 *
 * @param self	The dynamic array.
 * @param index	The index of the element to be retrieved.
 * @return		The value of the element at the specified index,
 					or NULL if the index is out of bounds.
 */
static void	*_get(t_cvector *self, size_t index)
{
	if (!self || index >= self->capacity)
		return (NULL);
	return (self->array + (index * self->type_size));
}

/**
 * @brief Destroys the dynamic array and frees the associated memory.
 *
 * @param self	The dynamic array to be destroyed.
 */
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

/**
 * @brief Creates a new dynamic type dinamic sized array.
 *
 * @param type_size		The size of each element in the dynamic array.
 * @param elem_destroy	A function pointer to a custom element
 							destruction function.
 * @return				A pointer to the newly created dynamic array,
 							or NULL if memory allocation fails.
 */
t_cvector	*cvector_new(size_t type_size, void (*elem_destroy)(void *))
{
	t_cvector	*vector;

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
