/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:48:36 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/20 22:52:56 by oishchen         ###   ########.fr       */
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
	while(++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			res.mtx[i][j] = 0;
			while(++k < 4)
				res.mtx[i][j] += mtx1->mtx[i][k] * mtx2->mtx[k][j];
		}
	}
	return (res);
}

double	std_determ(t_mtx2 *mtx1)
{
	double	res;

	res = mtx1->mtx[0][0] * mtx1->mtx[1][1] -
		mtx1->mtx[0][1] * mtx1->mtx[1][0];
	return (res);
}

t_mtx2	sub_mtx3(t_mtx3 *mtx, int row, int col)
{
	t_mtx2	res;

	if (col == 0)
	{
		res.mtx[0][0] = mtx->mtx[1][1];
		res.mtx[0][1] = mtx->mtx[1][2];
		res.mtx[1][0] = mtx->mtx[2][1];
		res.mtx[1][1] = mtx->mtx[2][2];
	}
	else if (col == 1)
	{
		res.mtx[0][0] = mtx->mtx[1][0];
		res.mtx[0][1] = mtx->mtx[1][2];
		res.mtx[1][0] = mtx->mtx[2][0];
		res.mtx[1][1] = mtx->mtx[2][2];
	}
	else
	{
		res.mtx[0][0] = mtx->mtx[1][0];
		res.mtx[0][1] = mtx->mtx[1][1];
		res.mtx[1][0] = mtx->mtx[2][0];
		res.mtx[1][1] = mtx->mtx[2][1];
	}
	return (res);
}

double	mtx3_determ(t_mtx3 *mtx1)
{
	
}

//t_mtx4	id_mtx(t_mtx4 *mtx)
//{
//	int		i;
//	int		j;
//	int		k;
//	t_mtx4	res;

//	i = -1;
//	while(++i < 4)
//	{
//		j = -1;
//		while (++j < 4)
//		{
//			k = -1;
//			res.mtx[i][j] = 0;
//			while (++k < 4)
//			{
//				if (i == j)
//					res.mtx[i][j] += mtx->mtx[i][j] * 1;
//				else
//					res.mtx[i][j] += mtx->mtx[i][j] * 0;
//			}
//		}
//	}
//	return (res);
//}


