#ifndef MINIRT_H
#define MINIRT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <MLX42.h>
#include <math.h>
#include <libft.h>
#include <fcntl.h>
#include <get_next_line.h>
#include <stdbool.h>
#include <limits.h>

int		is_rt(char *str);

# define SIZE_MTX4 4
# define SIZE_MTX3 3
# define SIZE_MTX2 2
# define PI 3.14159265358979323846
# define MAX_INTER 50
# define EPSILON 0.00001

typedef struct	s_vcpnt
{
	double	vp[4];
}	t_vcpnt;

typedef struct	s_ray
{
	t_vcpnt	pnt;
	t_vcpnt	vec;
}	t_ray;

typedef struct	s_mtx4
{
	double	mtx[4][4];
}	t_mtx4;

typedef struct	s_mtx2
{
	double	mtx[2][2];
}	t_mtx2;

typedef struct	s_mtx3
{
	double	mtx[3][3];
}	t_mtx3;

typedef struct s_test //delete
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

typedef struct	s_matirial
{
	t_vcpnt	color;
	double	ambient;
	double	specular;
	double	diffuse;
	double	shiness;
}	t_matirial;

typedef struct	s_light
{
	t_vcpnt	pnt_light;
	t_vcpnt	intens;
}	t_light;

typedef struct	s_sphere
{
	double		radi;
	t_matirial	mat;
	t_vcpnt		orig;
	t_mtx4		transform;
	t_mtx4		inv_mtx;
	t_mtx4		tr_inv_mtx;
}	t_sphere;

typedef struct	s_plane
{
	t_mtx4		transform;
	t_mtx4		inv_mtx;
	t_mtx4		tr_inv_mtx;
	t_matirial	mat;
}	t_plane;

typedef struct	s_sl
{
	double		radi;
	t_mtx4		transform;
	t_mtx4		inv_mtx;
	t_mtx4		tr_inv_mtx;
	t_vcpnt		orig;
	t_matirial	mat;
	int			is_closed;
	double		min;
	double		max;
}	t_cl;

typedef struct	s_camera
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

typedef struct	s_inter
{
	int			count;
	double		t;
	double		inter[2];
	t_obj		*obj;
}	t_inter;

typedef struct	s_world
{
	t_list	*objs;
	t_list	*lights;
	int		obj_n;
}	t_world;

typedef struct	s_hit
{
	double	min;
	int		pos;
	t_obj	*obj;
}	t_hit;

typedef struct 	s_prlgt
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
	double		last_mouse_x;
	double		last_mouse_y;
	bool		is_panning;
	bool		is_rotating;
	double		prev_mouse_x;
	double		prev_mouse_y;
}	t_master;

typedef struct s_mov_supp
{
	double	mov_speed;
	double	rot_speed;
	t_vcpnt	forward;
	t_vcpnt	right;
	t_vcpnt	wrld_up;
	t_vcpnt	mv_vec;
}	t_mov_supp;


t_test	*get_value(char *file);

// rays
int	inter_obj(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count);
int	inter_sp(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count);
t_ray		ray_transform(t_ray *ray, t_mtx4 *mtx);

// op vector && pointers
t_vcpnt	vec_reflect(t_vcpnt *in, t_vcpnt *norm);
t_vcpnt	vec_add(t_vcpnt *vec1, t_vcpnt *vec2);
t_vcpnt	vec_subs(t_vcpnt *vec1, t_vcpnt *vec2);
t_vcpnt	vec_muls(t_vcpnt *vec1, t_vcpnt *vec2);
double	vec_mag(t_vcpnt *vec);
t_vcpnt	vec_norm(t_vcpnt *vec);
t_vcpnt	vec_scale(t_vcpnt *vec, double scale);
void	vec_div(t_vcpnt *vec, double divisor);
double	vec_dot(t_vcpnt *vec1, t_vcpnt *vec2);
t_vcpnt	vec_cross(t_vcpnt *vec1, t_vcpnt *vec2);

// op matrixes/pointers/vectors
t_vcpnt	mult_mtx4_vcpnt4(t_mtx4 *mtx, t_vcpnt *pnt);

// op: rotation, scaling, transition, inv of those
t_mtx4	mtx4_ornt(t_vcpnt *left, t_vcpnt *true_up, t_vcpnt *forward);
t_mtx4	transpose(t_mtx4 *mtx);
t_mtx4	rotate_x(double rad_2_rotate);
t_mtx4	inv_rotate_x(double rad_2_rotate);
t_mtx4	rotate_y(double rad_2_rotate);
t_mtx4	inv_rotate_y(double rad_2_rotate);
t_mtx4	rotate_z(double rad_2_rotate);
t_mtx4	inv_rotate_z(double rad_2_rotate);
t_mtx4	scale4(t_vcpnt *vcpnt);
t_mtx4	inv_scale4(t_vcpnt *scale_vec);
t_mtx4	trnas4(t_vcpnt *trans_vec);
t_mtx4	inv_trnas4(t_vcpnt *trans_vec);
t_mtx4	shearing(t_vcpnt *sh1, t_vcpnt *sh2);

// op matrixes
void	create_transform_mtx4(t_obj *obj, t_mtx4 *new_mtx);
void	get_empty_mtx4(t_mtx4 *mtx);
void	get_id_mtx4(t_mtx4 *mtx);
t_mtx4	mtxs_mult4(t_mtx4 *mtx1, t_mtx4 *mtx2);
double	mtx2_determ(t_mtx2 *mtx1);
double	mtx3_determ(t_mtx3 *mtx3);
double	mtx4_determ(t_mtx4 *mtx4);
t_mtx4	mtx4_inverse(t_mtx4 *mtx);
t_mtx3	sub_mtx4(t_mtx4 *mtx, int row, int col);
t_mtx2	sub_mtx3(t_mtx3 *mtx, int row, int col);
//t_mtx4	id_mtx(t_mtx4 *mtx);

//delete
void	print_vpnt4(t_vcpnt *ent);
void	free_double(char **split);

//void	print_inv4(t_mtx4 *mtx);
void	pirnt_split_content(char **split);
void	print_mtx4(t_mtx4 *mtx);
void	print_mtx3(t_mtx3 *mtx);
void	print_mtx2(t_mtx2 *mtx);
int		get_rgba(int r, int g, int b, int a);
int		vcpnt_2_rgba(t_vcpnt *color);
void	default_world(t_world *wrld);

// create && print matrixes
void		create_mtx2_stb(t_mtx2 *mtx);
void		create_mtx3_stb(t_mtx3 *mtx);
void		create_mtx4_rnd(t_mtx4 *mtx);
void		create_mtx4_stb2(t_mtx4 *mtx);
void		create_mtx4_stb(t_mtx4 *mtx);
void		clean_lst(void *content);
//t_intersec	*hit(t_intersec *inter);

// object functions
t_vcpnt		normal_at(t_obj *obj, t_vcpnt *pnt);
t_vcpnt		normal_pl(t_plane *pl);
t_vcpnt		normal_sphere(t_sphere *obj, t_vcpnt *pnt);
t_type		get_obj(t_obj *obj);
t_obj		*sphere(t_matirial *mat, t_vcpnt *orig);
t_matirial	create_material(t_vcpnt	*color, double diffuse, double specular);
t_light		*create_light(t_vcpnt *pnt, t_vcpnt *color);
t_obj		*plane(void);
t_obj		*cylinder(t_matirial *mat, t_vcpnt *orig, double min, double max);
void		resize_cm(t_camera *cm, t_vcpnt	*new_from);
int			check_cap(t_ray *ray, double t);

//idk some taff calculation
t_vcpnt	alt_lighting(t_matirial *mat, t_light *light, t_vcpnt *pnt, t_vcpnt *eye, t_vcpnt *nrmvc);

// world_functions
t_world		init_world(void);
void		wadd_obj(t_world *world, t_light *light, t_obj *obj);
void		wclear_world(t_world *world);
t_vcpnt		world_inter(t_world *wrld, t_ray *r);

// camera functions
void		setup_camera(t_camera *c, double hsize, double vsize, double fov);
t_ray		ray_for_pixel(t_camera *camera, int	px, int py);
void		camera(t_camera *camera);
t_mtx4		view_transform(t_vcpnt *from, t_vcpnt *to, t_vcpnt *up);
t_mtx4		mtx4_ornt(t_vcpnt *left, t_vcpnt *true_up, t_vcpnt *forward);

// hooks
void	controls_hook(void *param);
void	render_hook(void *param);
void	render(t_world *w, t_camera *cm, mlx_image_t *img);

//light
t_prlgt	pre_calc(t_world *wrld, t_hit *hit, t_ray *r);
void	record_hit(t_hit *hit, t_inter *inter, int *pos);
int		is_inter_shd(t_world *wrld, t_ray *r, double dis);
t_vcpnt	lighting(t_matirial *mat, t_light *light, t_prlgt *l);
int		is_shadowed(t_world *wrld, t_vcpnt *pnt);

// undefinable stuff
void	ft_swap(double *t1, double *t2);

// mlx control
void	mlx_hook_keys(mlx_key_data_t keydata, void *master);
void	key_rotate(t_camera *cam, double yaw_speed, double pitch_speed);
t_mtx4	rotate_any_axis(t_vcpnt axis, double angle);
t_mtx4	rotate_any_axis(t_vcpnt axis, double angle);
void	mlx_hook_keys(mlx_key_data_t keydata, void *master);
void	mlx_hook_keys_supp(t_master *param, int key);
void	rotate_camera(t_master *param, int key);
void	resize_hook(int32_t width, int32_t height, void *param);

#endif