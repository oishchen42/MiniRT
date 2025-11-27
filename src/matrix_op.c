/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:48:36 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/27 19:13:00 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mtx4 mtxs_mult4(t_mtx4 *mtx1, t_mtx4 *mtx2)
{
	int		i;
	int		j;
	int		k;
	t_mtx4	res;

	i = -1;
	while(++i < SIZE_MTX4)
	{
		j = -1;
		while (++j < SIZE_MTX4)
		{
			k = -1;
			res.mtx[i][j] = 0;
			while(++k < SIZE_MTX4)
				res.mtx[i][j] += mtx1->mtx[i][k] * mtx2->mtx[k][j];
		}
	}
	return (res);
}

double	mtx2_determ(t_mtx2 *mtx1)
{
	double	res;

	res = mtx1->mtx[0][0] * mtx1->mtx[1][1] -
		mtx1->mtx[0][1] * mtx1->mtx[1][0];
	return (res);
}

t_mtx2	sub_mtx3(t_mtx3 *mtx, int row, int col)
{
	t_mtx2	res;
	int		j;
	int		i;
	int		k;
	int		l;

	i = -1;
	k = -1;
	while (++i < SIZE_MTX3)
	{
		j = -1;
		l = -1;
		if (i != row && j != col)
			k++;
		while (++j < SIZE_MTX3)
		{
			if (j != col && i != row)
			{
				++l;
				//printf("res.mtx[%d][%d]\n", k, l);
				res.mtx[k][l] = mtx->mtx[i][j];
			}
		}
	}
	return (res);
}

double	mtx3_determ(t_mtx3 *mtx3)
{
	double	minor_1;
	double	minor_2;
	double	minor_3;
	double	res;
	t_mtx2	mtx2;

	mtx2 = sub_mtx3(mtx3, 0, 0);
	minor_1 = mtx2_determ(&mtx2);
	mtx2 = sub_mtx3(mtx3, 0, 1);
	minor_2 = -1 * mtx2_determ(&mtx2);
	mtx2 = sub_mtx3(mtx3, 0, 2);
	minor_3 = mtx2_determ(&mtx2);
	//printf("determ 1: %f\n", minor_1); //delete
	//printf("determ 2: %f\n", minor_2);
	//printf("determ 3: %f\n", minor_3);
	res = mtx3->mtx[0][0] * minor_1 + mtx3->mtx[0][1] * minor_2 +
		mtx3->mtx[0][2] * minor_3;
	return (res);
}

t_mtx3	sub_mtx4(t_mtx4 *mtx, int row, int col)
{
	t_mtx3	res;
	int		j;
	int		i;
	int		k;
	int		l;

	i = -1;
	k = -1;
	while (++i < SIZE_MTX4)
	{
		j = -1;
		l = -1;
		if (i != row && j != col)
			k++;
		while (++j < SIZE_MTX4)
		{
			if (j != col && i != row)
			{
				++l;
				//printf("res.mtx[%d][%d]\n", k, l);
				res.mtx[k][l] = mtx->mtx[i][j];
			}
		}
	}
	return (res);
}

double	mtx4_determ(t_mtx4 *mtx4)
{
	double	minor_1;
	double	minor_2;
	double	minor_3;
	double	minor_4;
	double	res;
	t_mtx3	mtx3;

	mtx3 = sub_mtx4(mtx4, 0, 0);
	minor_1 = mtx3_determ(&mtx3);
	mtx3 = sub_mtx4(mtx4, 0, 1);
	minor_2 = -1 * mtx3_determ(&mtx3);
	mtx3 = sub_mtx4(mtx4, 0, 2);
	minor_3 = mtx3_determ(&mtx3);
	mtx3 = sub_mtx4(mtx4, 0, 3);
	minor_4 = -1 * mtx3_determ(&mtx3);
	res = mtx4->mtx[0][0] * minor_1 + mtx4->mtx[0][1] * minor_2 +
		mtx4->mtx[0][2] * minor_3 + mtx4->mtx[0][3] * minor_4;
	return (res);
}

t_mtx4	mtx4_inverse(t_mtx4 *mtx)
{
	int		i;
	int		j;
	double	determ;
	double	minor;
	t_mtx3	sub_mtx;
	t_mtx4	mtx_inver;

	i = -1;
	determ = mtx4_determ(mtx);
	//printf("determ: %f\n", determ);
	if (determ != 0)
	{
		while (++i < SIZE_MTX4)
		{
			j = -1;
			while (++j < SIZE_MTX4)
			{
				sub_mtx = sub_mtx4(mtx, i, j);
				//print_mtx3(&sub_mtx);
				//printf("------------------------------\n");
				minor = mtx3_determ(&sub_mtx);
				//printf("my powerfor row: %d col: %d is: %f\n", i, j, pow(-1.0, (double)i + j));
				//printf("my minor at[%d][%d] is: %.4f\n", i, j, minor);
				mtx_inver.mtx[j][i] = minor / determ * pow(-1.0, (double)i + j);
			}
		}
		return (mtx_inver);
	}
	return (*mtx);
}

void	get_empty_mtx4(t_mtx4 *mtx)
{
	int	j;
	int	i;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		j = -1;
		while (++j < SIZE_MTX4)
			mtx->mtx[i][j] = 0;
	}
}

void	create_transform_mtx4(t_mtx4 *priv_mtx, t_mtx4 *new_mtx)
{
	if (new_mtx == NULL)
	{
		get_empty_mtx4(priv_mtx);
		priv_mtx->mtx[0][0] = 1.0;
		priv_mtx->mtx[1][1] = 1.0;
		priv_mtx->mtx[2][2] = 1.0;
		priv_mtx->mtx[3][3] = 1.0;
	}
	else
		*priv_mtx = *new_mtx;
}

void	set_transform(t_sphere *sp, t_vcpnt *pnt_2_trans)
{
	t_mtx4	res;

	res = vcpnt4_2_mtx4(pnt_2_trans);
	sp->transform = res;
}
