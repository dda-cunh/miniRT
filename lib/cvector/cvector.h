/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cvector.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:40:10 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 18:44:58 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CVECTOR_H
# define CVECTOR_H

# include <stdlib.h>

# ifndef CVECTOR_INIT_CAP
#  define CVECTOR_INIT_CAP	9
# endif

# ifndef CVECTOR_SCALE
#  define CVECTOR_SCALE		2
# endif

typedef struct s_cvector
{
	unsigned char	*array;
	unsigned long	type_size;
	unsigned long	capacity;
	unsigned long	length;

	void			*(*get)(struct s_cvector *self, unsigned long index);
	void			(*set)(struct s_cvector *self, unsigned long index,
			void *content, int del_heap);
	void			(*add)(struct s_cvector *self, void *content, int del_heap);
	void			(*destroy)(struct s_cvector *self);
	void			(*elem_destroy)(void *element);
}	t_cvector;

t_cvector	*cvector_new(unsigned long type_size, void (*elem_destroy)(void *));

/* ************************************************************************** */
/*                                   MEMORY                                   */
/* ************************************************************************** */
void	*_realloc(void *ptr, size_t prev_size, size_t new_size);
void	*_memmove(void *dest, const void *src, size_t n);

#endif
