/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:55:11 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/25 15:47:08 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	null_terminated_matrix_len(void **matrix)
{
	size_t	i;

	i = 0;
	if (matrix)
		while (matrix[i])
			i++;
	return (i);
}

void	free_matrix(void **matrix, size_t lines)
{
	size_t	i;

	i = 0;
	if (!matrix)
		return ;
	while (i < lines)
	{
		if (matrix[i])
			free(matrix[i]);
		i++;
	}
	free(matrix);
}
