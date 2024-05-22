/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:47:23 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 19:26:04 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

# include "../lib/minilibx-linux/mlx_int.h"
# include "../lib/minilibx-linux/mlx.h"

# ifndef WINDOW_W
#  define WINDOW_W			1080
# endif
# ifndef WINDOW_H
#  define WINDOW_H			720
# endif

# define KEY_ARROW_RIGHT	65363
# define KEY_ARROW_LEFT		65361
# define KEY_ARROW_DOWN		65364
# define KEY_ARROW_UP		65362
# define KEY_ESC			65307

typedef struct s_color
{
	int	alpha;
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_window
{
	void			*mlx_ptr;
	void			*win_ptr;
}	t_window;

typedef struct s__img
{
	t_window	win;
	void		*ptr;
	char		*addr;
	int			w;
	int			h;
	int			bpp;
	int			endian;
	int			line_len;
}		t_image;

/* ************************************************************************** */
/*                                    IMAGE                                   */
/* ************************************************************************** */
t_color	get_image_pixel(t_image image, int x, int y);
t_image	new_image(int w, int h, t_window win);
void	set_image_pixel(t_image image, int x, int y, t_color color);
void	dump_image_window(t_image buffer);

/* ************************************************************************** */
/*                                    COLOR                                   */
/* ************************************************************************** */
t_color	int_to_color(int packed);
t_color	clamp_color(t_color c);
int		same_color(t_color a, t_color b);
int		color_to_int(t_color color);

#endif