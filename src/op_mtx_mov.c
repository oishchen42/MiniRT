/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_mtx_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 18:43:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/01 21:10:21 by oishchen         ###   ########.fr       */
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

t_mtx4	trnas4(t_vcpnt *trans_vec) // translation
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

t_mtx4	inv_trnas4(t_vcpnt *trans_vec)
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

t_mtx4	rotate_x(double rad_2_rotate)
{
	t_mtx4	mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[1][1] = cos(rad_2_rotate);
	mtx.mtx[2][2] = cos(rad_2_rotate);
	mtx.mtx[1][2] = -1 * sin(rad_2_rotate);
	mtx.mtx[2][1] = sin(rad_2_rotate);
	mtx.mtx[0][0] = 1.0;
	mtx.mtx[3][3] = 1.0;
	return (mtx);
}

t_mtx4	inv_rotate_x(double rad_2_rotate)
{
	t_mtx4	mtx;
	t_mtx4	inv_mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[1][1] = cos(rad_2_rotate);
	mtx.mtx[2][2] = cos(rad_2_rotate);
	mtx.mtx[1][2] = -1 * sin(rad_2_rotate);
	mtx.mtx[2][1] = sin(rad_2_rotate);
	mtx.mtx[0][0] = 1.0;
	mtx.mtx[3][3] = 1.0;
	inv_mtx = mtx4_inverse(&mtx);
	return (inv_mtx);
}

t_mtx4	rotate_y(double rad_2_rotate)
{
	t_mtx4	mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = cos(rad_2_rotate);
	mtx.mtx[0][2] = sin(rad_2_rotate);
	mtx.mtx[2][0] = -1 * sin(rad_2_rotate);
	mtx.mtx[2][2] = cos(rad_2_rotate);
	mtx.mtx[1][1] = 1.0;
	mtx.mtx[3][3] = 1.0;
	return (mtx);
}

t_mtx4	inv_rotate_y(double rad_2_rotate)
{
	t_mtx4	mtx;
	t_mtx4	inv_mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = cos(rad_2_rotate);
	mtx.mtx[0][2] = sin(rad_2_rotate);
	mtx.mtx[2][0] = -1 * sin(rad_2_rotate);
	mtx.mtx[2][2] = cos(rad_2_rotate);
	mtx.mtx[1][1] = 1.0;
	mtx.mtx[3][3] = 1.0;
	inv_mtx = mtx4_inverse(&mtx);
	return (inv_mtx);
}

t_mtx4	rotate_z(double rad_2_rotate)
{
	t_mtx4	mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = cos(rad_2_rotate);
	mtx.mtx[1][1] = cos(rad_2_rotate);
	mtx.mtx[0][1] = -1 * sin(rad_2_rotate);
	mtx.mtx[1][0] = sin(rad_2_rotate);
	mtx.mtx[2][2] = 1.0;
	mtx.mtx[3][3] = 1.0;
	return (mtx);
}

t_mtx4	inv_rotate_z(double rad_2_rotate)
{
	t_mtx4	mtx;
	t_mtx4	inv_mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = cos(rad_2_rotate);
	mtx.mtx[1][1] = cos(rad_2_rotate);
	mtx.mtx[0][1] = -1 * sin(rad_2_rotate);
	mtx.mtx[1][0] = sin(rad_2_rotate);
	mtx.mtx[2][2] = 1.0;
	mtx.mtx[3][3] = 1.0;
	inv_mtx = mtx4_inverse(&mtx);
	return (inv_mtx);
}