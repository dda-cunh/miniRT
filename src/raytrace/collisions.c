/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collisions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:17:09 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/06/02 22:40:37 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Returns a collision point structure representing no collision.
 * 
 * @return	The collision point structure with default values.
 */
t_coll_point3	get_no_collision(void)
{
	return ((t_coll_point3)
		{
			(t_point3){0, 0, 0}, (t_color){0, 0, 0, 0},
			(t_color){0, 0, 0, 0},
			(t_point3){0, 0, 0},
			INFINITY
		});
}

/**
 * Checks if a collision scalar value is considered valid.
 * 
 * @param scalar	The collision scalar value to check.
 * @return			True if the scalar is valid, false otherwise.
 */
bool	valid_collision(double scalar)
{
	return (scalar >= EPSILON && scalar < INFINITY);
}

static t_cvector	*new_coll_routine_data_arr(t_cvector *collidables,
												t_ray3 ray)
{
	t_coll_routine_data	new_elem;
	t_cvector			*arr;
	size_t				i;

	arr = cvector_new(sizeof(t_coll_routine_data), NULL);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < collidables->length)
	{
		new_elem = (t_coll_routine_data)
		{
			collidables->get(collidables, i),
			0,
			ray
		};
		arr->add(arr, &new_elem, false);
		i++;
	}
	return (arr);
}

/**
 * Performs collision detection for a ray with a list of collidable shapes.
 * 
 * @param ray		The ray to check for collision.
 * @param program	The program containing the list of collidable shapes.
 * @return			The collision point structure representing the closest collision.
 */
t_coll_point3	do_collisions(t_ray3 ray, t_prog *program)
{
	t_coll_point3	*worker_ret;
	t_coll_point3	min_coll;
	pthread_t		main_worker;

	min_coll = get_no_collision();
	if (pthread_create(&main_worker, NULL, async_rays_routine,
						new_coll_routine_data_arr(program->collidables, ray)))
		killprogram(EXIT_PTHREAD_CREATE, program);
	if (pthread_join(main_worker, (void **) &worker_ret))
		killprogram(EXIT_PTHREAD_JOIN, program);
	if (worker_ret)
	{
		min_coll = *worker_ret;
		free(worker_ret);
	}
	return (min_coll);
}
