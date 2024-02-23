/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:23:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/02/23 18:27:21 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx-linux/mlx_int.h"
# include "minilibx-linux/mlx.h"
# include "libft/libft.h"
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# ifndef WINDOW_W
#  define WINDOW_W		720
# endif
# ifndef WINDOW_H
#  define WINDOW_H		720
# endif

# ifndef EPSILON
#  define EPSILON		0.00000000000001
# endif

# define SHADOW_BIAS	0.001

# define SHADOW_RATIO	0.1f

# define BAD_EXIT		"Error\n"

# define CVECTOR_INIT_CAP	9
# define CVECTOR_SCALE		2

# define OBJ_TO_COLL_SHAPE	&(t_collidable_shape){(t_object_cylinder *)

typedef struct	s_cvector
{
	unsigned char		*array;
	size_t				type_size;
	size_t				capacity;
	size_t				length;

	unsigned char		*(*get)(struct s_cvector *self, size_t index);
	void				(*set)(struct s_cvector *self, size_t index, void *content);
	void				(*add)(struct s_cvector *self, void *content);
	void				(*destroy)(struct s_cvector *self);
	void				(*elem_destroy)(void *element);
}	t_cvector;

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
	int						alpha;
	int						red;
	int						green;
	int						blue;
}	t_color;

# define COLOR_WHITE			(t_color){255, 255, 255, 255}
# define COLOR_BLACK			(t_color){255, 0, 0, 0}
# define COLOR_GREEN			(t_color){255, 0, 255, 0}
# define COLOR_BLUE				(t_color){255, 0, 0, 255}
# define COLOR_RED				(t_color){255, 255, 0, 0}

struct s_vec2
{
	double						x;
	double						y;
};

typedef struct s_vec2	t_point2;
typedef struct s_vec2	t_vec2;

struct s_vec3
{
	double						x;
	double						y;
	double						z;
};

typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_vec3;

# define ORIGIN					(t_point3){0, 0, 0}

typedef struct s_ray3
{
	t_point3					origin;
	t_vec3						direction;
}	t_ray3;

typedef struct s_coll_point3
{
	t_point3					coords;
	t_color						color;
	t_vec3						normal;
	double						scalar;
}	t_coll_point3;

# define NO_COLLISION			(t_coll_point3){ORIGIN, COLOR_BLACK, ORIGIN, INFINITY}

typedef struct s_camera
{
	t_point3					coords;
	t_vec3						forward;
	t_vec3						right;
	t_vec3						up;
	int							fov;
	double						tan_fov;
}	t_camera;

typedef struct s_light
{
	t_point3					coords;
	t_color						color;
	double						ratio;
}	t_light;

typedef enum e_collidable_id
{
	ID_EMPTY,
	ID_CYLINDER,
	ID_SPHERE,
	ID_PLANE
}	t_collidable_id;

typedef struct s_object_plane
{
	t_collidable_id				_id;
	t_point3					point;
	t_color						color;
	t_vec3						normal;

	void						(*destroy)(struct s_object_plane *self);
	t_coll_point3				(*collide)(struct s_object_plane *self,
		t_ray3 ray);
}	t_object_plane;

typedef struct s_object_cylinder
{
	t_collidable_id				_id;
	t_object_plane				*disk1;
	t_object_plane				*disk2;
	t_point3					center;
	t_color						color;
	t_vec3						axis;
	double						diameter;
	double						height;
	double						radius;

	void						(*destroy)(struct s_object_cylinder *self);
	t_coll_point3				(*collide)(struct s_object_cylinder *self,
			t_ray3 ray);
}	t_object_cylinder;

typedef struct s_object_sphere
{
	t_collidable_id				_id;
	t_point3					center;
	t_color						color;
	double						diameter;

	void						(*destroy)(struct s_object_sphere *self);
	t_coll_point3				(*collide)(struct s_object_sphere *self,
			t_ray3 ray);
}	t_object_sphere;

typedef union u_collidable_shape
{
	t_object_cylinder			*cy;
	t_object_sphere				*sp;
	t_object_plane				*pl;
}	t_collidable_shape;

typedef struct s_coll_arr
{
	t_collidable_shape			**ent;
	int							length;

	void						(*destroy)(struct s_coll_arr *self);
}	t_coll_shape_arr;

typedef struct s_prog
{
	t_coll_point3				**collisions;
	t_cvector					*collidables;
	t_cvector					*lights;
	t_camera					camera;
	t_light						ambient_l;
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
t_prog				*init_program(int scene_fd);
int					killprogram(int keycode, t_prog *program);
int					key_hook(int keycode, t_prog *window);
int					kill_x(void *program);

/* ************************************************************************** */
/*                                  RAYTRACE                                  */
/* ************************************************************************** */
t_coll_point3		do_collisions(t_ray3 ray, t_prog *program);
t_coll_point3		**do_rays(t_prog *program);
bool				valid_collision(double scalar);
void				trace(t_prog *program);

/* ************************************************************************** */
/*                                   MATH                                     */
/* ************************************************************************** */
t_point3			point3_plus_vec3(t_point3 point, t_vec3 vector);
t_vec3				vec3_from_points(t_point3 start, t_point3 end);
t_vec3				scale_vec3(t_vec3 vector, double scalar);
t_vec3				vec3_cross_product(t_vec3 a, t_vec3 b);
t_vec3				normalize_vec3(t_vec3 vector);
t_vec3				vec3_sub(t_vec3 a, t_vec3 b);
double				quadratic_smallest_pos(double a, double b, double c);
double				point3_distance_point3(t_point3 p1, t_point3 p2);
double				pythagorean_theorem(double a, double b);
double				vec3_dot_product(t_vec3 a, t_vec3 b);
bool				point3_inside_sphere(t_point3 point,
						t_object_sphere sphere);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
t_exit_status		__on_exit(t_exit_status exit_code, char *verbose);
t_image				new_image(int w, int h, t_prog program);
t_color				blend_colors(t_color original, double intensity,
						t_color to_apply);
t_color				get_image_pixel(t_image image, int x, int y);
t_color				sum_colors(t_color color1, t_color color2);
t_color				int_to_color(int packed);
void				set_image_pixel(t_image image, int x, int y, t_color color);
void				free_matrix(void **matrix, size_t lines);
void				dump_image_window(t_image buffer);
bool				same_color(t_color a, t_color b);
int					color_to_int(t_color color);

/* ************************************************************************** */
/*                                 T_TYPES                                    */
/* ************************************************************************** */
t_collidable_shape	*new_collidable_shape(void *t_object);
t_coll_shape_arr	*coll_shape_arr_new(int length);
t_object_cylinder	*new_cylinder(t_object_cylinder cy);
t_object_sphere		*new_sphere(t_point3 center, t_color color, double diameter);
t_collidable_id		get_coll_shape_id(t_collidable_shape ent);
t_object_plane		*new_plane(t_point3 point, t_color color, t_vec3 normal);
t_cvector			*cvector_new(size_t type_size,
						void (*elem_destroy)(void *));
void				destroy_collidable_shape(void *shape);

#endif