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


typedef struct	s_vcpnt
{
	double	vp[4];
}	t_vcpnt;

typedef struct	s_mtx
{
	double	mtx[4][4];
}	t_mtx4;

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

// op matrixes
t_mtx4 mtxs_mult(t_mtx4 *mtx1, t_mtx4 *mtx2);

//delete
void 	free_double(char **split);
void	pirnt_split_content(char **split);
void	create_mtx(t_mtx4 *mtx);
void	print_mtx(t_mtx4 *mtx);


#endif