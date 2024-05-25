/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analizer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 10:25:19 by arabelo-          #+#    #+#             */
/*   Updated: 2024/05/25 15:52:23 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_exit_status	object_analizer(char *line)
{
	char			**array;
	t_exit_status	res;

	array = ft_split(line, ' ');
	if (!array)
		return (EXIT_MALLOC);
	if (!ft_strncmp(array[0], "A", 2))
		res = build_ambient_light(array);
	else if (!ft_strncmp(array[0], "C", 2))
		res = build_camera(array);
	else if (!ft_strncmp(array[0], "L", 2))
		res = build_light(array);
	else
		res = set_collidable(array);
	free_matrix((void **)array, null_terminated_matrix_len((void *)array));
	return (res);
}
