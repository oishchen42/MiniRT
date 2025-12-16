/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:27:51 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 21:27:54 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>abedeuet 
# include <limits.h>
# include "MLX42.h"
# include "libft.h"
# include "get_next_line.h"

/* Defines */
# define SIZE_MTX4	4
# define SIZE_MTX3	3
# define SIZE_MTX2	2
# define PI 		3.14159265358979323846
# define MAX_INTER	50
# define EPSILON	0.00001

/* Typedefs & Structs */

typedef struct s_vcpnt
{
	double	vp[4];
}	t_vcpnt;

typedef struct s_ray
{
	t_vcpnt	pnt;
	t_vcpnt	vec;
}	t_ray;

typedef struct s_mtx4
{
	double	mtx[4][4];
}	t_mtx4;

typedef struct s_mtx2
{
	double	mtx[2][2];
}	t_mtx2;

typedef struct s_mtx3
{
	double	mtx[3][3];
}	t_mtx3;

typedef struct s_test
{
	char	*type;
	float	value1;
	t_vcpnt	vec1;
}	t_test;

typedef enum e_type
{
	SPHERE,
	PLANE,
	CYLINDER,
}	t_type;

typedef struct s_material
{
	t_vcpnt	color;
	double	ambient;
	double	specular;
	double	diffuse;
	double	shiness;
}	t_material;

typedef struct s_light
{
	t_vcpnt	pnt_light;
	t_vcpnt	intens;
}	t_light;

typedef struct s_sphere
{
	double		radi;
	t_material	mat;
	t_vcpnt		orig;
	t_mtx4		transform;
	t_mtx4		inv_mtx;
	t_mtx4		tr_inv_mtx;
}	t_sphere;

typedef struct s_plane
{
	t_mtx4		transform;
	t_mtx4		inv_mtx;
	t_mtx4		tr_inv_mtx;
	t_material	mat;
}	t_plane;

typedef struct s_sl
{
	double		radi;
	t_mtx4		transform;
	t_mtx4		inv_mtx;
	t_mtx4		tr_inv_mtx;
	t_vcpnt		orig;
	t_material	mat;
	int			is_closed;
	double		min;
	double		max;
}	t_cl;

typedef struct s_camera
{
	double	half_view;
	double	aspect;
	double	hsize;
	double	vsize;
	double	half_width;
	double	half_height;
	double	pixel_size;
	double	field_of_view;
	t_mtx4	transform;
	t_mtx4	inv_trans;
	t_vcpnt	from;
	t_vcpnt	to;
	t_vcpnt	up;
}	t_camera;

typedef union u_obj_data
{
	t_sphere	sp;
	t_plane		pl;
	t_cl		cl;
}	t_obj_data;

typedef struct s_obj
{
	t_type		type;
	t_obj_data	data;
	int			n;
}	t_obj;

typedef struct s_supitr
{
	double	a;
	double	b;
	double	c;
	double	disc;
	t_ray	lcl;
	double	t1;
	double	t2;
	double	temp;
	double	y0;
	double	y1;
	int		bl;
}	t_supitr;

typedef struct s_inter
{
	int		count;
	double	t;
	double	inter[2];
	t_obj	*obj;
}	t_inter;

typedef struct s_world
{
	t_list	*objs;
	t_list	*lights;
	int		obj_n;
}	t_world;

typedef struct s_hit
{
	double	min;
	int		pos;
	t_obj	*obj;
}	t_hit;

typedef struct s_prlgt
{
	t_obj	*obj;
	t_vcpnt	scaledv;
	t_vcpnt	hit_pnt;
	t_vcpnt	over_pnt;
	t_vcpnt	eyev;
	t_vcpnt	normv;
	bool	is_inside;
	double	t;
	t_vcpnt	eff_clr;
	t_vcpnt	lightv;
	t_vcpnt	lightv_nrm;
	t_vcpnt	ambient;
	double	light_dot_nrm;
	t_vcpnt	diffuse;
	t_vcpnt	specular;
	t_vcpnt	neg_lightv;
	t_vcpnt	reflectiv;
	double	reflect_dot_eye;
	t_vcpnt	res;
}	t_prlgt;

typedef struct s_master
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_world		world;
	t_camera	camera;
}	t_master;

#endif