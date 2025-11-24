/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mtx_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:15:29 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/24 21:35:30 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	mult_mtx4_vcpnt4(t_mtx4 *mtx, t_vcpnt *pnt)
{
	int		i;
	t_vcpnt	res;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		res.vp[i] = (mtx->mtx[i][0] * pnt->vp[0]) +
					(mtx->mtx[i][1] * pnt->vp[1]) +
					(mtx->mtx[i][2] * pnt->vp[2]) +
					(mtx->mtx[i][3] * pnt->vp[3]);
	}
	return (res);
}

t_vcpnt	trnas4(t_vcpnt *trans_vec, t_vcpnt *p_to_move)
{
	t_mtx4	mtx;
	int		i;
	t_vcpnt	res;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][3] = trans_vec->vp[0];
	mtx.mtx[1][3] = trans_vec->vp[1];
	mtx.mtx[2][3] = trans_vec->vp[2];
	mtx.mtx[3][3] = 1.0;
	mtx.mtx[2][2] = 1.0;
	mtx.mtx[1][1] = 1.0;
	mtx.mtx[0][0] = 1.0;
	res = mult_mtx4_vcpnt4(&mtx, p_to_move);
	return (res);
}

t_vcpnt	scale4(t_vcpnt *scale_vec, t_vcpnt *p_2_scale)
{
	t_mtx4	mtx;
	int		i;
	t_vcpnt	res;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = scale_vec->vp[0];
	mtx.mtx[1][1] = scale_vec->vp[1];
	mtx.mtx[2][2] = scale_vec->vp[2];
	mtx.mtx[3][3] = 1.0;
	res = mult_mtx4_vcpnt4(&mtx, p_2_scale);
	return (res);
}

t_vcpnt	rotate_x(double rad_2_rotate, t_vcpnt *p_2_rotate)
{
	t_mtx4	mtx;
	int		i;
	t_vcpnt	res;

	get_empty_mtx4(&mtx);
	mtx.mtx[1][1] = cos(rad_2_rotate);
	mtx.mtx[2][2] = cos(rad_2_rotate);
	mtx.mtx[1][2] = -1 * sin(rad_2_rotate);
	mtx.mtx[2][1] = sin(rad_2_rotate);
	mtx.mtx[0][0] = 1.0;
	mtx.mtx[3][3] = 1.0;
	res = mult_mtx4_vcpnt4(&mtx, p_2_rotate);
	return (res);
}

t_vcpnt	rotate_y(double rad_2_rotate, t_vcpnt *p_2_rotate)
{
	t_mtx4	mtx;
	int		i;
	t_vcpnt	res;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = cos(rad_2_rotate);
	mtx.mtx[0][2] = sin(rad_2_rotate);
	mtx.mtx[2][0] = -1 * sin(rad_2_rotate);
	mtx.mtx[2][2] = cos(rad_2_rotate);
	mtx.mtx[1][1] = 1.0;
	mtx.mtx[3][3] = 1.0;
	res = mult_mtx4_vcpnt4(&mtx, p_2_rotate);
	return (res);
}

t_vcpnt	rotate_z(double rad_2_rotate, t_vcpnt *p_2_rotate)
{
	t_mtx4	mtx;
	int		i;
	t_vcpnt	res;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = cos(rad_2_rotate);
	mtx.mtx[1][1] = cos(rad_2_rotate);
	mtx.mtx[0][1] = -1 * sin(rad_2_rotate);
	mtx.mtx[1][0] = sin(rad_2_rotate);
	mtx.mtx[2][2] = 1.0;
	mtx.mtx[3][3] = 1.0;
	res = mult_mtx4_vcpnt4(&mtx, p_2_rotate);
	return (res);
}
