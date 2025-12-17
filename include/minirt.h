/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:27:43 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/17 23:22:38 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structs.h"

/* Function Prototypes */

int			is_rt(char *str);
t_test		*get_value(char *file);

/* Rays */
int			inter_obj(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count);
int			inter_sp(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count);
t_ray		ray_transform(t_ray *ray, t_mtx4 *mtx);

/* Vector Operations */
t_vcpnt		vec_reflect(t_vcpnt *in, t_vcpnt *norm);
t_vcpnt		vec_add(t_vcpnt *vec1, t_vcpnt *vec2);
t_vcpnt		vec_subs(t_vcpnt *vec1, t_vcpnt *vec2);
t_vcpnt		vec_muls(t_vcpnt *vec1, t_vcpnt *vec2);
double		vec_mag(t_vcpnt *vec);
t_vcpnt		vec_norm(t_vcpnt *vec);
t_vcpnt		vec_scale(t_vcpnt *vec, double scale);
void		vec_div(t_vcpnt *vec, double divisor);
double		vec_dot(t_vcpnt *vec1, t_vcpnt *vec2);
t_vcpnt		vec_cross(t_vcpnt *vec1, t_vcpnt *vec2);

/* Matrix & Vector Math */
t_vcpnt		mult_mtx4_vcpnt4(t_mtx4 *mtx, t_vcpnt *pnt);

/* Transformations (Rot, Scale, Trans) */
t_mtx4		mtx4_ornt(t_vcpnt *left, t_vcpnt *true_up, t_vcpnt *forward);
t_mtx4		transpose(t_mtx4 *mtx);
t_mtx4		rotate_x(double rad_2_rotate);
t_mtx4		inv_rotate_x(double rad_2_rotate);
t_mtx4		rotate_y(double rad_2_rotate);
t_mtx4		inv_rotate_y(double rad_2_rotate);
t_mtx4		rotate_z(double rad_2_rotate);
t_mtx4		inv_rotate_z(double rad_2_rotate);
t_mtx4		scale4(t_vcpnt *vcpnt);
t_mtx4		inv_scale4(t_vcpnt *scale_vec);
t_mtx4		trans4(t_vcpnt *trans_vec);
t_mtx4		inv_trans4(t_vcpnt *trans_vec);
t_mtx4		shearing(t_vcpnt *sh1, t_vcpnt *sh2);

/* Matrix Operations */
void		create_transform_mtx4(t_obj *obj, t_mtx4 *new_mtx);
void		get_empty_mtx4(t_mtx4 *mtx);
void		get_id_mtx4(t_mtx4 *mtx);
t_mtx4		mtxs_mult4(t_mtx4 *mtx1, t_mtx4 *mtx2);
double		mtx2_determ(t_mtx2 *mtx1);
double		mtx3_determ(t_mtx3 *mtx3);
double		mtx4_determ(t_mtx4 *mtx4);
t_mtx4		mtx4_inverse(t_mtx4 *mtx);
t_mtx3		sub_mtx4(t_mtx4 *mtx, int row, int col);
t_mtx2		sub_mtx3(t_mtx3 *mtx, int row, int col);

/* Utils / Printing / Freeing */
void		print_vpnt4(t_vcpnt *ent);
void		free_double(char **split);
void		default_world(t_world *wrld);
void		pirnt_split_content(char **split);
void		print_mtx4(t_mtx4 *mtx);
void		print_mtx3(t_mtx3 *mtx);
void		print_mtx2(t_mtx2 *mtx);
int			get_rgba(int r, int g, int b, int a);
int			vcpnt_2_rgba(t_vcpnt *color);
void		ft_swap(double *t1, double *t2);
void		clean_lst(void *content);

/* Create Matrixes */
void		create_mtx2_stb(t_mtx2 *mtx);
void		create_mtx3_stb(t_mtx3 *mtx);
void		create_mtx4_rnd(t_mtx4 *mtx);
void		create_mtx4_stb2(t_mtx4 *mtx);
void		create_mtx4_stb(t_mtx4 *mtx);

/* Object Functions */
t_vcpnt		normal_at(t_obj *obj, t_vcpnt *pnt);
t_vcpnt		normal_pl(t_plane *pl);
t_vcpnt		normal_sphere(t_sphere *obj, t_vcpnt *pnt);
t_type		get_obj(t_obj *obj);
t_obj		*sphere(t_material *mat, t_vcpnt *orig);
t_material	create_material(t_vcpnt *color, double diffuse, double specular);
t_light		*create_light(t_vcpnt *pnt, t_vcpnt *color);
t_obj		*plane(void);
t_obj		*cylinder(t_matirial *mat, t_vcpnt *orig, double min, double max);
void		resize_cm(t_camera *cm, t_vcpnt	*new_from);
int			check_cup(t_ray *ray, double t);

/* World Functions */
t_world		init_world(void);
void		add_obj(t_world *world, t_light *light, t_obj *obj);
void		wclear_world(t_world *world);
t_vcpnt		world_inter(t_world *wrld, t_ray *r);

/* Camera Functions */
void		setup_camera(t_camera *c, double hsize, double vsize, double fov);
t_ray		ray_for_pixel(t_camera *camera, int px, int py);
void		camera(t_camera *camera);
t_mtx4		view_transform(t_vcpnt *from, t_vcpnt *to, t_vcpnt *up);

/* Hooks & Rendering */
void		controls_hook(void *param);
void		render_hook(void *param);
void		render(t_world *w, t_camera *cm, mlx_image_t *img);

//light
t_prlgt	pre_calc(t_world *wrld, t_hit *hit, t_ray *r);
void	record_hit(t_hit *hit, t_inter *inter, int *pos);
int		is_inter_shd(t_world *wrld, t_ray *r, double dis);
t_vcpnt	lighting(t_matirial *mat, t_light *light, t_prlgt *l);
int		is_shadowed(t_world *wrld, t_vcpnt *pnt);

// undefinable stuff
void	ft_swap(double *t1, double *t2);

#endif