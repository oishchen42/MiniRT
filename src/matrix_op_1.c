/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:48:36 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 05:51:08 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mtx4	mtxs_mult4(t_mtx4 *mtx1, t_mtx4 *mtx2)
{
	int		i;
	int		j;
	int		k;
	t_mtx4	res;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		j = -1;
		while (++j < SIZE_MTX4)
		{
			k = -1;
			res.mtx[i][j] = 0;
			while (++k < SIZE_MTX4)
				res.mtx[i][j] += mtx1->mtx[i][k] * mtx2->mtx[k][j];
		}
	}
	return (res);
}

double	mtx2_determ(t_mtx2 *mtx1)
{
	double	res;

	res = mtx1->mtx[0][0] * mtx1->mtx[1][1]
		- mtx1->mtx[0][1] * mtx1->mtx[1][0];
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
	res = mtx3->mtx[0][0] * minor_1 + mtx3->mtx[0][1] * minor_2
		+ mtx3->mtx[0][2] * minor_3;
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
				res.mtx[k][l] = mtx->mtx[i][j];
			}
		}
	}
	return (res);
}
