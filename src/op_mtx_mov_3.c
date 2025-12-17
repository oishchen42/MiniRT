/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_mtx_mov_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:52:57 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 21:22:58 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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

t_mtx4	shearing(t_vcpnt *sh1, t_vcpnt *sh2)
{
	t_mtx4	res;

	get_empty_mtx4(&res);
	res.mtx[0][1] = sh1->vp[0];
	res.mtx[0][2] = sh1->vp[1];
	res.mtx[1][0] = sh1->vp[2];
	res.mtx[1][2] = sh2->vp[0];
	res.mtx[2][0] = sh2->vp[1];
	res.mtx[2][1] = sh2->vp[2];
	return (res);
}
