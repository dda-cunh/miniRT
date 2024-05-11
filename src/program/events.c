/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:33:58 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/11 12:10:48 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

/**
 * Handles key events.
 *
 * @param keycode	The keycode of the pressed key.
 * @param program	A pointer to the program structure.
 * @return			Returns 0 if no action is taken.
 */
int	key_hook(int keycode, t_prog *program)
{
	if (keycode == KEY_ESC)
		return (killprogram(0, program));
	return (0);
}

/**
 * Terminates the program when the 'x' button is clicked.
 *
 * @param program A pointer to the program structure.
 */
int	kill_x(void *program)
{
	exit(killprogram(0, program));
}
