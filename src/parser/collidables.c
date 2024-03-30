/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collidables.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:41:58 by arabelo-          #+#    #+#             */
/*   Updated: 2024/03/30 11:13:20 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_exit_status	set_collidable(char **array)
{
	if (!get_program()->collidables)
	{
		get_program()->collidables = cvector_new(sizeof(t_collidable_shape),
		&destroy_collidable_shape);
		if (!get_program()->collidables)
			return (EXIT_MALLOC);
	}
	if (!ft_strncmp(array[0], "sp", 3))
		return (build_sphere(array));
	else if (!ft_strncmp(array[0], "pl", 3))
		return (build_plane(array));
	else if (!ft_strncmp(array[0], "cy", 3))
		return (build_cylinder(array));
	return (INVALID_OBJECT);
}
