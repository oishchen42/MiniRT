/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_mtx_mov_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:52:26 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 21:22:28 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
