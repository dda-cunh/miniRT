/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:23:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/01/12 14:54:45 by dda-cunh         ###   ########.fr       */
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

# ifndef WINDOW_H
#  define WINDOW_H	720
# endif
# ifndef WINDOW_W
#  define WINDOW_W	720
# endif

# define BAD_EXIT	"Error\n"



typedef unsigned char	t_byte;

typedef enum exit_status
{
	EXIT_GOOD,
	EXIT_MALLOC,
	EXIT_ARGC,
	EXIT_FILE_EXTENSION,
	EXIT_OPENING_SCENE,
	EXIT_SCENE,
	EXIT_MLX
}	t_exit_status;

typedef struct s_color
{
	t_byte						alpha;
	t_byte						red;
	t_byte						green;
	t_byte						blue;
}	t_color;

struct s_vec2
{
	float						x;
	float						y;
};

typedef struct s_vec2	t_point2;
typedef struct s_vec2	t_vec2;

struct s_vec3
{
	float						x;
	float						y;
	float						z;
};

typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_vec3;

typedef struct s_ray3
{
	t_point3					origin;
	t_vec3						direction;
}	t_ray3;

typedef struct s_camera
{
	t_point3					coords;
	t_vec3						look_direction;
	t_byte						fov;
}	t_camera;

typedef struct s_light
{
	t_point3					coords;
	t_color						color;
}	t_light;

typedef enum e_collidable_id
{
	ID_EMPTY,
	ID_CYLINDER,
	ID_SPHERE,
	ID_PLANE
}	t_collidable_id;

typedef struct s_object_cylinder
{
	t_point3					center;
	t_color						color;
	t_vec3						axis;
	float						diameter;
	float						height;
}	t_object_cylinder;

typedef struct s_object_sphere
{
	t_point3					center;
	t_color						color;
	float						diameter;
}	t_object_sphere;

typedef struct s_object_plane
{
	t_point3					point;
	t_color						color;
	t_vec3						normal;
}	t_object_plane;

typedef union u_collidable_shape
{
	t_object_cylinder			cy;
	t_object_sphere				sp;
	t_object_plane				pl;
}	t_collidable_shape;

typedef struct s_collidable_entity
{
	t_collidable_shape	object;
	t_collidable_id		id;
}	t_collidable_entity;

typedef struct s_prog
{
	t_camera					camera;
	t_list						*collidables;
	t_list						*lights;
	t_color						ambient_l;
	void						*mlx_ptr;
	void						*win_ptr;
}	t_prog;

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
t_prog			*init_program(int scene_fd);
int				killprogram(int keycode, t_prog *program);
int				key_hook(int keycode, t_prog *window);
int				kill_x(void *program);

/* ************************************************************************** */
/*                                  RAYTRACE                                  */
/* ************************************************************************** */
void			do_rays(t_prog *program);
int				do_collisions(t_ray3 ray, t_prog *program);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
t_collidable_entity	*new_collidable_entity(t_collidable_shape *shape,
		t_collidable_id id);
t_exit_status	__on_exit(t_exit_status exit_code, char *verbose);
t_point3		point3_plus_vec3(t_point3 point, t_vec3 vector);
t_color			get_pixel_color(t_image image, int x, int y);
t_color			sum_colors(t_color color1, t_color color2);
t_color			int_to_color(int packed);
t_image			new_image(int w, int h, t_prog program);
t_vec3			scale_vec3(t_vec3 vector, float scalar);
t_vec3			normalize_vec3(t_vec3 vector);
float			point3_distance_point3(t_point3 p1, t_point3 p2);
void			set_image_pixel(t_image image, int x, int y, t_color color);
int				color_to_int(t_color color);

#endif