#ifndef MINIRT_H
#define MINIRT_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
// #include <MLX42.h>
#include <math.h>
#include <libft.h>
#include <fcntl.h>
#include <get_next_line.h>

int		is_rt(char *str);

# define SIZE_MTX4 4
# define SIZE_MTX3 3
# define SIZE_MTX2 2

typedef struct s_sphere
{
	double	radi;
	t_vcpnt	orig;
}	t_spere;


typedef struct	s_vcpnt
{
	double	vp[4];
}	t_vcpnt;

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

t_test	*get_value(char *file);

// op math_tuples
t_vcpnt	tuple_mul(t_mtx4 *mtx1, t_vcpnt *tpl);

// op vector && pointers
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

// op: rotation, scaling, transition
t_vcpnt	rotate_x(double rad_2_rotate, t_vcpnt *p_2_rotate);
t_vcpnt	rotate_y(double rad_2_rotate, t_vcpnt *p_2_rotate);
t_vcpnt	rotate_z(double rad_2_rotate, t_vcpnt *p_2_rotate);
t_vcpnt	scale4(t_vcpnt *scale_vec, t_vcpnt *p_2_scale);
t_vcpnt	trnas4(t_vcpnt *trans_vec, t_vcpnt *p_to_move);

// op matrixes
void	get_empty_mtx4(t_mtx4 *mtx);
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
void 	free_double(char **split);
void	print_inv4(t_mtx4 *mtx);
void	pirnt_split_content(char **split);
void	print_mtx4(t_mtx4 *mtx);
void	print_mtx3(t_mtx3 *mtx);
void	print_mtx2(t_mtx2 *mtx);

// create && print matrixes
void	create_mtx2_stb(t_mtx2 *mtx);
void	create_mtx3_stb(t_mtx3 *mtx);
void	create_mtx4_rnd(t_mtx4 *mtx);
void	create_mtx4_stb2(t_mtx4 *mtx);
void	create_mtx4_stb(t_mtx4 *mtx);

#endif