/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:23:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2023/11/05 16:20:22 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define WINDOW_W	1280
# define WINDOW_H	720
# define BYTE		unsigned char

typedef enum exit_status
{
	_GOOD,
	_MALLOC,
	_SCENE
}	t_exit_status;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vec3	t_point3;

typedef struct s_vec3	t_vec3;

typedef struct s_color
{
	BYTE	alpha;
	BYTE	red;
	BYTE	green;
	BYTE	blue;
}	t_color;

typedef struct s_object_sphere
{
	t_point3	center;
	t_color		color;
	double		diameter;
}	t_object_sphere;

typedef struct s_map
{
	char	**lines;
	int		width;
	int		height;
	int		pmoves;
	char	underp;
}		t_map;

typedef struct s_camera
{
	t_point3	coords;
	t_vec3		look_direction;
	t_vec3		up_direction;
	BYTE		fov;
}	t_camera;

typedef struct s_prog
{
	t_map	mapold;
	t_map	map;
	void	*mlx_ptr;
	void	*win_ptr;
	int		status;
}		t_prog;

typedef struct s__img
{
	t_prog	win;
	void	*ptr;
	char	*addr;
	int		w;
	int		h;
	int		bpp;
	int		endian;
	int		line_len;
}		t_image;

/* ************************************************************************** */
/*                                   PROGRAM                                  */
/* ************************************************************************** */
t_prog			*new_program(char *title);
/* ************************************************************************** */
/*                                 window.c                                   */
/* ************************************************************************** */
void			put_object(char object, t_prog *p, int event, int *coords);
void			render_map(t_prog *program, int event, int firstrender);
char			*get_path(char object, int event);

/* ************************************************************************** */
/*                                  image.c                                   */
/* ************************************************************************** */
t_color			get_pixel_color(t_image image, int x, int y);
void			print_blend(t_prog *prog, t_image t, t_image u, int *coords);
t_image			new_image(int w, int h, t_prog window);
void			print_floor(t_prog *program);

/* ************************************************************************** */
/*                                events.c                                    */
/* ************************************************************************** */
int				killprogram(int keycode, t_prog *program);
int				key_hook(int keycode, t_prog *window);
int				kill_x(void *program);

/* ************************************************************************** */
/*                                  map.c                                     */
/* ************************************************************************** */
t_map			get_map(int mapfd, char *map_path);

/* ************************************************************************** */
/*                                 utils.c                                    */
/* ************************************************************************** */
int				exit_(int status);
char			**copy2d(char **map, int height);
void			putstr_footer(t_prog *program, int y, int color);
void			clearendbl(char **matrix);
void			free_2d(char **matrix);

/* ************************************************************************** */
/*                                  path.c                                    */
/* ************************************************************************** */
int				parse_path(t_map map);

/* ************************************************************************** */
/*                                player.c                                    */
/* ************************************************************************** */
int				*object_coords(char object, char **map, int width, int height);
void			try_move(int direction, t_prog *program);
void			move_player(t_prog *prog, int event, int *coords);

#endif