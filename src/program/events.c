/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:33:58 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/11/03 16:09:24 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	key_hook(int keycode, t_prog *program)
{
	if (keycode == 65307)
		return (killprogram(0, program));
	if (keycode == 119)
		try_move(1, program);
	else if (keycode == 97)
		try_move(2, program);
	else if (keycode == 115)
		try_move(3, program);
	else if (keycode == 100)
		try_move(4, program);
	return (0);
}

int	kill_x(void *program)
{
	exit(killprogram(0, program));
}
