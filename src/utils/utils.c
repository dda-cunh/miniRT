/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:07:53 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/12 14:55:06 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	print_exit_msg(t_exit_status exit_code, char *verbose)
{
	if (exit_code == EXIT_MALLOC)
		ft_putstr_fd("Failed Malloc:\t", STD_ERR);
	//TODO else if...
	//
	//
	ft_putstr_fd(verbose, STD_ERR);
	ft_putchar_fd('\n', STD_ERR);
	return;
}

t_exit_status	__on_exit(t_exit_status exit_code, char *verbose)
{
	if (exit_code != EXIT_GOOD)
	{
		ft_putstr_fd(BAD_EXIT, STD_ERR);
		print_exit_msg(exit_code, verbose);
	}
	return (exit_code);
}

t_collidable_entity	*new_collidable_entity(t_collidable_shape *shape,
		t_collidable_id id)
{
	t_collidable_entity	*obj;

	obj = malloc(sizeof(t_collidable_entity));
	if (!obj)
		return (NULL);
	obj->id = id;
	obj->object = *shape;
	free(shape);
	return (obj);
}