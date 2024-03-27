/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arabelo- <arabelo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 12:07:53 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/03/27 17:14:13 by arabelo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	print_exit_msg(t_exit_status exit_code, char *verbose)
{
	if (exit_code == EXIT_MALLOC)
		ft_putstr_fd("Failed Malloc:\t", STD_ERR);
	else if (exit_code == EXIT_ARGC)
		ft_putstr_fd("Wrong number of parameters:\t", STD_ERR);
	else if (exit_code == EXIT_FILE_EXTENSION)
		ft_putstr_fd("Wrong file extension:\t", STD_ERR);
	else if (exit_code == EXIT_OPENING_SCENE)
		ft_putstr_fd("Failure at open:\t", STD_ERR);
	else if (exit_code == EXIT_CLOSE)
		ft_putstr_fd("Close failed:\t", STD_ERR);
	else if (exit_code == EXIT_SCENE)
		ft_putstr_fd("Bad Scene:\t", STD_OUT);
	else if (exit_code == EXIT_MLX)
		ft_putstr_fd("MLX failed:\t", STD_OUT);
	else if (exit_code == EXIT_GOOD)
		ft_putstr_fd("Clean exit:\t", STD_OUT);
	else
		check_msg(exit_code);
	ft_putstr_fd(verbose, STD_ERR);
	ft_putchar_fd('\n', STD_ERR);
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

void	free_matrix(void **matrix, size_t lines)
{
	size_t	i;

	i = 0;
	if (matrix)
	{
		while (i < lines)
		{
			if (matrix[i])
				free(matrix[i]);
			i++;
		}
		free(matrix);
	}
}

t_prog	*get_program(void)
{
	static t_prog	prog;

	return (&prog);
}

bool    ft_isspace(int c)
{
    return (c == ' ' || (c >= '\t' && c <= '\r'));
}
