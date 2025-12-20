/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 21:27:43 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 06:14:23 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structs.h"

/* Rays */
int			inter_obj(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count);
int			inter_sp(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count);
int			inter_cl(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count);
void		get_inter(t_obj *obj, int count, double t, t_inter *inter);
void		record_t12(t_supitr *itr);
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
t_vcpnt		normal_cl(t_cl *cl, t_vcpnt *world_pnt);
t_type		get_obj(t_obj *obj);
t_obj		*sphere(t_vcpnt *clr);
t_material	create_material(t_vcpnt *color, double diffuse, double specular);
t_light		*create_light(t_vcpnt *pnt, t_vcpnt *color, double ratio);
t_obj		*plane(t_vcpnt *clr);
t_obj		*cylinder(t_vcpnt *clr, t_vcpnt *orig, double min, double max);
void		resize_cm(t_camera *cm, t_vcpnt	*new_from);
int			check_cap(t_ray *ray, double t);

/* World Functions */
t_world		init_world(void);
void		wadd_obj(t_world *world, t_light *light, t_obj *obj);
void		wclear_world(t_world *world);
t_vcpnt		world_inter(t_master *app, t_ray *r);

/* Camera Functions */
void		setup_camera(t_camera *c, double hsize, double vsize, double fov);
t_ray		ray_for_pixel(t_camera *camera, int px, int py);
void		camera(t_camera *camera);
t_mtx4		view_transform(t_vcpnt *from, t_vcpnt *to);

/* Hooks & Rendering */
void		controls_hook(void *param);
void		render_hook(void *param);
void		render(t_master *app, t_camera *cm, mlx_image_t *img);

//light
t_prlgt		pre_calc(t_master *app, t_hit *hit, t_ray *r);
void		record_hit(t_hit *hit, t_inter *inter, int *pos);
int			is_inter_shd(t_world *wrld, t_ray *r, double dis);
t_vcpnt		lighting(t_material *mat, t_light *light, t_prlgt *l);
int			is_shadowed(t_world *wrld, t_vcpnt *pnt);
void		sp_pre_light(t_master *app, t_prlgt *pr, t_light *l);
void		sp_pre_plane(t_master *app, t_prlgt *pr, t_light *l);
void		sp_pre_cylinder(t_master *app, t_prlgt *pr, t_light *l);
t_vcpnt		shade_hit(t_world *w, t_prlgt *l);

/* MLX_control */
void		mlx_hook_keys(mlx_key_data_t keydata, void *master);
void		key_rotate(t_camera *cam, double yaw_speed, double pitch_speed);
t_mtx4		rotate_any_axis(t_vcpnt axis, double angle);
t_mtx4		rotate_any_axis(t_vcpnt axis, double angle);
void		mlx_hook_keys(mlx_key_data_t keydata, void *master);
void		mlx_hook_keys_supp(t_master *param, int key);
void		rotate_camera(t_master *param, int key);
void		resize_hook(int32_t width, int32_t height, void *param);

/*Parsing*/
int			parse_data(t_master *app, char *file);
int			parse_line(t_master *app, char *line);
int			check_extension(char *filename);
t_mtx4		get_rotation_matrix(t_vcpnt *orient);
int			check_extension(char *filename);
int			check_main_obj(t_master *app);
int			parse_figures(t_master *app, char **tokens);
int			parse_mobjects(t_master *app, char **tokens);

/*Parsing objects*/
int			pr_amb(t_master *app, char **tokens);
int			parse_2camera(t_master *app, char **tokens, t_cm_pr *pr_cm);
int			pr_cm(t_master *app, char **tokens);
int			parse_light(t_master *app, char **tokens);
int			pr_sp(t_master *app, char **tokens);
int			pr_pl(t_master *app, char **tokens);
int			pr_cl(t_master *app, char **tokens);

/*Parsing support functions*/
int			check_normalized(t_vcpnt *vec);
void		record_cl_values(t_cl_pr cl_pr);
int			valid_str(char *str);

/*Support libft functons*/
void		from_high_2_low(t_vcpnt *vcpnt);
int			get_vector(char *str, t_vcpnt *vec, double is_pnt);
int			check_tokens(char **split);
t_master	init_master(void);
void		ft_swap(double *t1, double *t2);
void		free_split(char **split);
t_material	init_mat(void);
double		ft_atod(char *str);

/*Cleanups && errors_prints*/
int			prnt_err(char *str);
int			p_err(char *msg, t_master *app, bool is_exit_nrm);
int32_t		ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

#endif