/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coll_routine_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:41:05 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/06/02 16:52:34 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_coll_routine_data	*new_coll_routine_data_arr(size_t length)
{
	t_coll_routine_data	*arr;
	size_t				i;

	arr = ft_calloc(length, sizeof(t_coll_routine_data));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < length)
	{
		arr[i].curr_ent = NULL;
		arr[i].ray = (t_ray3){(t_point3){0, 0, 0}, (t_vec3){0, 0, 0}};
		arr[i].thread = 0;
		i++;
	}
	return (arr);
}
