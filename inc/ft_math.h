/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-cunh <dda-cunh@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:17:44 by dda-cunh          #+#    #+#             */
/*   Updated: 2024/05/22 19:44:25 by dda-cunh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include <math.h>

struct s_vec2
{
	double	x;
	double	y;
};

typedef struct s_vec2	t_point2;
typedef struct s_vec2	t_vec2;

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_vec3;

typedef struct s_ray3
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray3;

/* ************************************************************************** */
/*                                     VEC                                    */
/* ************************************************************************** */
double		vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec3		vec3_from_points(t_point3 start, t_point3 end);
t_vec3		scale_vec3(t_vec3 vector, double scalar);
t_vec3		vec3_cross_product(t_vec3 a, t_vec3 b);
t_vec3		normalize_vec3(t_vec3 vector);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);

/* ************************************************************************** */
/*                                    POINT                                   */
/* ************************************************************************** */
t_point3	point3_plus_vec3(t_point3 point, t_vec3 vector);
double		point3_distance_point3(t_point3 p1, t_point3 p2);

/* ************************************************************************** */
/*                                   COMMON                                   */
/* ************************************************************************** */
double		quadratic_smallest_pos(double a, double b, double c);
double		clamp_value(double value, double min, double max);
double		pythagorean_theorem(double a, double b);

#endif
