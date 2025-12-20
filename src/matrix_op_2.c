/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_op_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:54:26 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 05:50:38 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

//Timo updated function. More then 5 vars. Instead of seperate calculation
//for each matrix element it will be added to res after each operation
double	mtx4_determ(t_mtx4 *mtx4)
{
	double	res;
	t_mtx3	mtx3;

	mtx3 = sub_mtx4(mtx4, 0, 0);
	res = mtx4->mtx[0][0] * mtx3_determ(&mtx3);
	mtx3 = sub_mtx4(mtx4, 0, 1);
	res += mtx4->mtx[0][1] * -1.0 * mtx3_determ(&mtx3);
	mtx3 = sub_mtx4(mtx4, 0, 2);
	res += mtx4->mtx[0][2] * mtx3_determ(&mtx3);
	mtx3 = sub_mtx4(mtx4, 0, 3);
	res += mtx4->mtx[0][3] * -1.0 * mtx3_determ(&mtx3);
	return (res);
}

t_mtx4	mtx4_inverse(t_mtx4 *mtx)
{
	int		i;
	int		j;
	double	determ;
	t_mtx3	sub_mtx;
	t_mtx4	mtx_inver;

	i = -1;
	determ = mtx4_determ(mtx);
	if (determ != 0)
	{
		while (++i < SIZE_MTX4)
		{
			j = -1;
			while (++j < SIZE_MTX4)
			{
				sub_mtx = sub_mtx4(mtx, i, j);
				mtx_inver.mtx[j][i] = mtx3_determ(&sub_mtx)
					/ determ * pow(-1.0, (double)i + j);
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
			mtx->mtx[i][j] = 0.0;
	}
}

void	get_id_mtx4(t_mtx4 *mtx)
{
	int	j;
	int	i;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		j = -1;
		while (++j < SIZE_MTX4)
		{
			if (i == j)
				mtx->mtx[i][j] = 1.0;
			else
				mtx->mtx[i][j] = 0.0;
		}
	}
}

void	set_transform(t_sphere *sp, t_vcpnt *pnt_2_trans)
{
	t_mtx4	res;

	res = trans4(pnt_2_trans);
	sp->transform = res;
}
