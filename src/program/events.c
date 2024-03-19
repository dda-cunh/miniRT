/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:33:58 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/19 12:32:50 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	key_hook(int keycode, t_prog *program)
{
	if (keycode == KEY_ESC)
		return (killprogram(0, program));
	return (0);
}

int	kill_x(void *program)
{
	exit(killprogram(0, program));
}
