/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_orient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:28:35 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/18 22:52:30 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	fill_mtx_xyz(t_mtx4 res, t_vcpnt new_x, t_vcpnt new_y, t_vcpnt new_z)
{
	res.mtx[0][0] = new_x.vp[0];
	res.mtx[1][0] = new_x.vp[1];
	res.mtx[2][0] = new_x.vp[2];
	res.mtx[0][1] = new_y.vp[0];
	res.mtx[1][1] = new_y.vp[1];
	res.mtx[2][1] = new_y.vp[2];
	res.mtx[0][2] = new_z.vp[0];
	res.mtx[1][2] = new_z.vp[1];
	res.mtx[2][2] = new_z.vp[2];
}

t_mtx4	get_rotation_matrix(t_vcpnt *orient)
{
	t_mtx4	res;
	t_vcpnt new_y;
	t_vcpnt new_x;
	t_vcpnt new_z;
	t_vcpnt guide;

	new_y = vec_norm(orient);
	if (fabs(new_y.vp[0]) < EPSILON && fabs(new_y.vp[2]) < EPSILON)
	{
		get_id_mtx4(&res);
		if (new_y.vp[1] < 0) 
			res.mtx[1][1] = -1;
		return (res);
	}
	guide = (t_vcpnt){0, 1, 0, 0};
	new_x = vec_cross(&new_y, &guide);
	new_x = vec_norm(&new_x);
	new_z = vec_cross(&new_x, &new_y);
	new_z = vec_norm(&new_z);
	get_id_mtx4(&res);
	fill_mtx_xyz(res, new_x, new_y, new_z);
	return (res);
}
