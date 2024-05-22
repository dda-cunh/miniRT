/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:48:06 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/07 14:53:14 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putdigs_fd(int n, int fd)
{
	if (n <= -10 || n >= 10)
	{
		ft_putdigs_fd(n / 10, fd);
		ft_putdigs_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(ft_abs(n) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	ft_putdigs_fd(n, fd);
}
