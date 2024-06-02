/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   async_rays.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 21:41:58 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/06/02 23:03:16 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Wrapper function to call the appropriate collision function
 	based on the collidable shape type.
 * 
 * @param ray		The ray to check for collision.
 * @param curr_ent	The current collidable shape.
 * @return			The collision point structure representing the collision.
 */
static t_coll_point3	coll_func_wrapper(t_ray3 ray,
	t_collidable_shape *curr_ent)
{
	t_collidable_id	id;

	if (curr_ent)
	{
		id = get_coll_shape_id(*curr_ent);
		if (id == ID_CYLINDER)
			return (curr_ent->cy->collide(curr_ent->cy, ray));
		else if (id == ID_SPHERE)
			return (curr_ent->sp->collide(curr_ent->sp, ray));
		else if (id == ID_PLANE)
			return (curr_ent->pl->collide(curr_ent->pl, ray));
	}
	return (get_no_collision());
}

static void	*coll_routine(void *arg)
{
	t_coll_routine_data	*data;
	t_coll_point3		*collision;

	collision = NULL;
	data = (t_coll_routine_data *) arg;
	if (data)
	{
		collision = malloc(sizeof(t_coll_point3));
		*collision = coll_func_wrapper(data->ray, data->curr_ent);
	}
	return ((void *) collision);
}

void	*async_rays_routine(void *arg)
{
	t_coll_routine_data	*curr;
	t_coll_point3		*thread_ret;
	t_coll_point3		*min_coll;
	t_cvector			*data;
	size_t				i;

	data = (t_cvector *) arg;
	if (!data)
		return (NULL);
	i = 0;
	while (i < data->length)
	{
		curr = data->get(data, i);
		if (pthread_create(&curr->thread, NULL, &coll_routine,
				curr))
			killprogram(EXIT_PTHREAD_JOIN, get_program());
		i++;
	}
	i = 0;
	min_coll =  ft_calloc(1, sizeof(t_coll_point3));
	*min_coll = get_no_collision();
	while (i < data->length)
	{
		curr = data->get(data, i);
		if (pthread_join(curr->thread, (void **) &thread_ret))
			killprogram(EXIT_PTHREAD_JOIN, get_program());
		if (thread_ret)
		{
			if (valid_collision(thread_ret->scalar)
				&& thread_ret->scalar < min_coll->scalar)
				*min_coll = *thread_ret;
			free(thread_ret);
		}
		i++;
	}
	data->destroy(data);
	return ((void *) min_coll);
}
