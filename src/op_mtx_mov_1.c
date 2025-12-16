/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_mtx_mov_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:43:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/16 21:21:36 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mtx4	transpose(t_mtx4 *mtx)
{
	t_mtx4	trans;
	int		i;
	int		j;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		j = -1;
		while (++j < SIZE_MTX4)
			trans.mtx[i][j] = mtx->mtx[j][i];
	}
	return (trans);
}

t_mtx4	trans4(t_vcpnt *trans_vec) // translation
{
	t_mtx4	mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][3] = trans_vec->vp[0];
	mtx.mtx[1][3] = trans_vec->vp[1];
	mtx.mtx[2][3] = trans_vec->vp[2];
	mtx.mtx[3][3] = 1.0;
	mtx.mtx[2][2] = 1.0;
	mtx.mtx[1][1] = 1.0;
	mtx.mtx[0][0] = 1.0;
	return (mtx);
}

t_mtx4	inv_trans4(t_vcpnt *trans_vec)
{
	t_mtx4	mtx;
	t_mtx4	inv_mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][3] = trans_vec->vp[0];
	mtx.mtx[1][3] = trans_vec->vp[1];
	mtx.mtx[2][3] = trans_vec->vp[2];
	mtx.mtx[3][3] = 1.0;
	mtx.mtx[2][2] = 1.0;
	mtx.mtx[1][1] = 1.0;
	mtx.mtx[0][0] = 1.0;
	inv_mtx = mtx4_inverse(&mtx);
	return (inv_mtx);
}

t_mtx4	scale4(t_vcpnt *vcpnt)
{
	t_mtx4	mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = vcpnt->vp[0];
	mtx.mtx[1][1] = vcpnt->vp[1];
	mtx.mtx[2][2] = vcpnt->vp[2];
	mtx.mtx[3][3] = 1.0;
	return (mtx);
}

t_mtx4	inv_scale4(t_vcpnt *scale_vec)
{
	t_mtx4	mtx;
	t_mtx4	inv_mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = scale_vec->vp[0];
	mtx.mtx[1][1] = scale_vec->vp[1];
	mtx.mtx[2][2] = scale_vec->vp[2];
	mtx.mtx[3][3] = 1.0;
	inv_mtx = mtx4_inverse(&mtx);
	return (inv_mtx);
}
