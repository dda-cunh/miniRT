/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:23:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/06/03 11:13:15 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>

# include "../lib/cvector/cvector.h"
# include "../lib/libft/libft.h"

# include "display.h"
# include "ft_math.h"

# ifndef EPSILON
#  define EPSILON			0.000001
# endif

# define SHADOW_BIAS		0.001

# define GLOSSINESS			48

# define BAD_EXIT			"Error\n"

# define MAX_RATIO			1.0
# define MIN_RATIO			0.0
# define FOV_MAX			180
# define FOV_MIN			0 
# define MAX_VECT			1.0
# define MIN_VECT			-1.0

# define CHECK_FAILURE		0
# define CHECK_SUCCESS		1

typedef enum exit_status
{
	EXIT_GOOD,					// 0
	EXIT_MALLOC, 				// 1
	EXIT_ARGC,					// 2
	EXIT_FILE_EXTENSION,		// 3
	EXIT_OPENING_SCENE,			// 4
	EXIT_CLOSE,					// 5
	EXIT_SCENE,					// 6
	EXIT_MLX,					// 7
	EXIT_MISSING_OBJ,			// 8
	INVALID_OBJECT,				// 9
	OBJECT_ALREADY_IN_USE,		// 10
	WRONG_INFO_AMOUNT,			// 11
	BAD_RGB_FORMAT,				// 12
	BAD_COORDS_FORMAT,			// 13
	BAD_RATIO_RANGE,			// 14
	FOV_OUT_OF_RANGE,			// 15
	VEC_OUT_OF_RANGE,			// 16
	INVALID_SPHERE_DIAMETER,	// 17
	INVALID_CYLINDER_DIAMETER,	// 18
	INVALID_CYLINDER_HEIGHT,	// 19
	INVALID_RATIO_FORMAT,		// 20
	BAD_VEC_FORMAT,				// 21
	NOTHING_TO_RENDER,			// 22
	__LEN_EXIT_ENUM				// 23
}	t_exit_status;

typedef struct s_coll_point3
{
	t_point3	coords;
	t_color		coll_color;
	t_color		visible_color;
	t_vec3		normal;
	double		scalar;
}	t_coll_point3;

typedef struct s_camera
{
	t_point3	coords;
	t_vec3		forward;
	t_vec3		right;
	t_vec3		up;
	int			fov;
	double		tan_fov;
	bool		is_already_in_use;
}	t_camera;

typedef struct s_light
{
	t_point3	coords;
	t_color		color;
	double		ratio;
	bool		is_already_in_use;
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
	t_collidable_id	_id;
	t_point3		point;
	t_color			color;
	t_vec3			normal;

	void			(*destroy)(struct s_object_plane *self);
	t_coll_point3	(*collide)(struct s_object_plane * self, t_ray3 ray);
}	t_object_plane;

typedef struct s_object_cylinder
{
	t_collidable_id	_id;
	t_object_plane	*disk1;
	t_object_plane	*disk2;
	t_point3		center;
	t_color			color;
	t_vec3			axis;
	double			diameter;
	double			height;
	double			radius;

	void			(*destroy)(struct s_object_cylinder *self);
	t_coll_point3	(*collide)(struct s_object_cylinder * self, t_ray3 ray);
}	t_object_cylinder;

typedef struct s_object_sphere
{
	t_collidable_id	_id;
	t_point3		center;
	t_color			color;
	double			diameter;

	void			(*destroy)(struct s_object_sphere *self);
	t_coll_point3	(*collide)(struct s_object_sphere * self, t_ray3 ray);
}	t_object_sphere;

typedef union u_collidable_shape
{
	t_object_cylinder	*cy;
	t_object_sphere		*sp;
	t_object_plane		*pl;
}	t_collidable_shape;

typedef struct s_prog
{
	t_coll_point3		**collisions;
	t_cvector			*collidables;
	t_light				light;
	t_camera			camera;
	t_light				ambient_l;
	t_window			win;
}	t_prog;

/* ************************************************************************** */
/*                                   PROGRAM                                  */
/* ************************************************************************** */
t_prog				*get_program(void);
int					killprogram(int keycode, t_prog *program);
int					key_hook(int keycode, t_prog *program);
int					kill_x(void *program);

/* ************************************************************************** */
/*                                  RAYTRACE                                  */
/* ************************************************************************** */
t_coll_point3		get_no_collision(void);
bool				valid_collision(double scalar);
t_coll_point3		do_collisions(t_ray3 ray, t_prog *program);
void				do_rays(t_prog *program);
void				trace(t_prog *program);
t_color				lighting(t_coll_point3 coll, t_vec3 to_light,
						t_light light);

/* ************************************************************************** */
/*                                   UTILS                                    */
/* ************************************************************************** */
t_exit_status		__on_exit(t_exit_status exit_code, char *verbose);
bool				check_rgb_string_format(char *rgb, int nums_counter);
bool				check_vec_string_format(char *vec, int nums_counter);
void				free_matrix(void **matrix, size_t lines);
void				check_msg(t_exit_status code);
void				check_msg2(t_exit_status code);

/* ************************************************************************** */
/*                                 T_TYPES                                    */
/* ************************************************************************** */
t_collidable_shape	*new_collidable_shape(void *t_object);
t_object_cylinder	*new_cylinder(t_object_cylinder cy);
t_object_sphere		*new_sphere(t_point3 center, t_color color,
						double diameter);
t_collidable_id		get_coll_shape_id(t_collidable_shape ent);
t_object_plane		*new_plane(t_point3 point, t_color color, t_vec3 normal);
void				destroy_collidable_shape(void *shape);

/* ************************************************************************** */
/*                                 PARSER                                     */
/* ************************************************************************** */
t_exit_status		check_coords_vec_rgb(char **coords,
						char **vec, char **rgb);
t_exit_status		check_coords_rgb(char **rgb, char **coords);
t_exit_status		check_vec_orientation(char **vec_orien);
t_exit_status		build_ambient_light(char **array);
t_exit_status		build_cylinder(char **array);
t_exit_status		set_collidable(char **array);
t_exit_status		object_analizer(char *line);
t_exit_status		build_camera(char **array);
t_exit_status		build_sphere(char **array);
t_exit_status		build_light(char **array);
t_exit_status		build_plane(char **array);
bool				validate_fractional_value(char *coord);
bool				is_file_extension_valid(char *file);
bool				is_file_extension_valid(char *file);
bool				check_coordinates(char **coords);
bool				check_rgb_format(char **rgb);
bool				check_double_var(char *str);
bool				only_digits(char *str);
void				parser(char *file);

#endif