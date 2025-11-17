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


typedef struct	s_vector
{
	double x;
	double y;
	double z;
}	t_vec;

typedef struct	s_matrix
{
	double row;
	double col;
}	t_matrix;

typedef struct s_test
{
	char *type;
	float value1;
	t_vec vec1;
}	t_test;

t_test	*get_value(char *file);

//delete
void 	free_double(char **split);
void	pirnt_split_content(char **split);

#endif