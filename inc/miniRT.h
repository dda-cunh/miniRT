/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:23:12 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/10 20:46:30 by dda-cunh         ###   ########.fr       */
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
#  define WINDOW_W			1080
# endif
# ifndef WINDOW_H
#  define WINDOW_H			720
# endif

# ifndef EPSILON
#  define EPSILON			0.000001
# endif

# define SHADOW_BIAS		0.001

# define GLOSSINESS			48

# define BAD_EXIT			"Error\n"

# define KEY_ARROW_RIGHT	65363
# define KEY_ARROW_LEFT		65361
# define KEY_ARROW_DOWN		65364
# define KEY_ARROW_UP		65362
# define KEY_ESC			65307

# define CVECTOR_INIT_CAP	9
# define CVECTOR_SCALE		2

# define MAX_RATIO 1.0
# define MIN_RATIO 0.0
# define FOV_MAX 180
# define FOV_MIN 0 
# define MAX_VECT 1.0
# define MIN_VECT -1.0

typedef struct	s_cvector
{
	unsigned char		*array;
	size_t				type_size;
	size_t				capacity;
	size_t				length;

	void				*(*get)(struct s_cvector *self, size_t index);
	void				(*set)(struct s_cvector *self, size_t index, void *content, bool del_heap);
	void				(*add)(struct s_cvector *self, void *content, bool del_heap);
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
	EXIT_MLX,
	EXIT_MISSING_OBJ,
	CHECK_FAILURE,
	CHECK_SUCCESS,
	INVALID_OBJECT,
	OBJECT_ALREADY_IN_USE,
	WRONG_INFO_AMOUNT,
	BAD_RGB_FORMAT,
	BAD_COORDS_FORMAT,
	BAD_RATIO_RANGE,
	EXIT_CLOSE,
	FOV_OUT_OF_RANGE,
	VEC_OUT_OF_RANGE,
	INVALID_SPHERE_DIAMETER,
	INVALID_CYLINDER_DIAMETER,
	INVALID_CYLINDER_HEIGHT,
	INVALID_RATIO_FORMAT
}	t_exit_status;

typedef struct s_color
{
	int						alpha;
	int						red;
	int						green;
	int						blue;
}	t_color;

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

typedef struct s_ray3
{
	t_point3					origin;
	t_vec3						direction;
}	t_ray3;

typedef struct s_coll_point3
{
	t_point3					coords;
	t_color						coll_color;
	t_color						visible_color;
	t_vec3						normal;
	double						scalar;
}	t_coll_point3;

typedef struct s_camera
{
	t_point3					coords;
	t_vec3						forward;
	t_vec3						right;
	t_vec3						up;
	int							fov;
	double						tan_fov;
	bool						is_already_in_use;
}	t_camera;

typedef struct s_light
{
	t_point3					coords;
	t_color						color;
	double						ratio;
	bool						is_already_in_use;
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


typedef struct s_prog
{
	t_coll_point3				**collisions;
	t_cvector					*collidables;
	t_light						light;
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
t_prog				*get_program(void);
int					killprogram(int keycode, t_prog *program);
int					key_hook(int keycode, t_prog *window);
int					kill_x(void *program);

/* ************************************************************************** */
/*                                  RAYTRACE                                  */
/* ************************************************************************** */
t_coll_point3		do_collisions(t_ray3 ray, t_prog *program);
void				do_rays(t_prog *program);
t_coll_point3		get_no_collision(void);
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
t_color				lighting(t_coll_point3 coll, t_vec3 to_light,
						t_light light);
t_color				get_image_pixel(t_image image, int x, int y);
t_color				sum_colors(t_color color1, t_color color2);
t_color				int_to_color(int packed);
void				set_image_pixel(t_image image, int x, int y, t_color color);
void				free_matrix(void **matrix, size_t lines);
void				dump_image_window(t_image buffer);
size_t				array_len(char **array);
bool				same_color(t_color a, t_color b);
int					color_to_int(t_color color);
void				check_msg(t_exit_status code);
t_color				append_colors(t_color a, double b_intensity, t_color b);
bool				check_rgb_string_format(char *rgb, int nums_counter);

/* ************************************************************************** */
/*                                 T_TYPES                                    */
/* ************************************************************************** */
t_collidable_shape	*new_collidable_shape(void *t_object);
t_object_cylinder	*new_cylinder(t_object_cylinder cy);
t_object_sphere		*new_sphere(t_point3 center, t_color color,
						double diameter);
t_collidable_id		get_coll_shape_id(t_collidable_shape ent);
t_object_plane		*new_plane(t_point3 point, t_color color, t_vec3 normal);
t_cvector			*cvector_new(size_t type_size,
						void (*elem_destroy)(void *));
void				destroy_collidable_shape(void *shape);

/* ************************************************************************** */
/*                                 PARSER                                     */
/* ************************************************************************** */
bool				is_file_extension_valid(char *file);
void				parser(char *file);
bool				check_double_var(char *str);
bool				only_digits(char *str);
bool				check_rgb_format(char **rgb);
bool				is_file_extension_valid(char *file);
bool				validate_fractional_value(char *coord);
bool				check_coordinates(char **coords);
t_exit_status		check_coords_rgb(char **rgb, char **coords);
t_exit_status		check_coords_vec_rgb(char **coords,
						char **vec, char **rgb);
t_exit_status		object_analizer(char *line);
t_exit_status		check_vec_orientation(char **vec_orien);
t_exit_status		build_ambient_light(char **array);
t_exit_status		build_camera(char **array);
t_exit_status		build_light(char **array);
t_exit_status		build_sphere(char **array);
t_exit_status		build_plane(char **array);
t_exit_status		build_cylinder(char **array);
t_exit_status		set_collidable(char **array);

#endif