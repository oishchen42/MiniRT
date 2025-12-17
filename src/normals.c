/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:05:27 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/18 00:07:15 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	normal_sphere(t_sphere *obj, t_vcpnt *pnt)
{
	t_vcpnt	local;
	t_vcpnt	local_nrm;
	t_vcpnt	wrld_nrm;

	local = mult_mtx4_vcpnt4(&obj->inv_mtx, pnt);
	local_nrm = vec_subs(&local, &((t_vcpnt){0,0,0,1}));
	wrld_nrm = mult_mtx4_vcpnt4(&obj->tr_inv_mtx, &local_nrm);
	return (vec_norm(&wrld_nrm));
}

t_vcpnt	normal_pl(t_plane *pl)
{
	t_vcpnt	std;
	t_vcpnt	wrld_nrm;

	std = (t_vcpnt){0, 1, 0, 0};
	wrld_nrm = mult_mtx4_vcpnt4(&pl->tr_inv_mtx, &std);
	return (vec_norm(&wrld_nrm));
}

t_vcpnt normal_cl(t_cl *cl, t_vcpnt *world_pnt)
{
	t_vcpnt	local_pnt;
	t_vcpnt	local_nrm;
	t_vcpnt	wrld_nrm;
	double	dis;

	local_pnt = mult_mtx4_vcpnt4(&cl->inv_mtx, world_pnt);
	dis = pow(local_pnt.vp[0], 2.0) + pow(local_pnt.vp[2], 2.0);
	if (dis < 1.0 && local_pnt.vp[1] >= cl->max - EPSILON)
		local_nrm = (t_vcpnt){0,1,0,0};
	else if (dis < 1.0 && local_pnt.vp[1] <= cl->min + EPSILON)
		local_nrm = (t_vcpnt){0,-1,0,0};
	else
		local_nrm = (t_vcpnt){local_pnt.vp[0], 0, local_pnt.vp[2], 0};
	wrld_nrm = mult_mtx4_vcpnt4(&cl->tr_inv_mtx, &local_nrm);
	wrld_nrm.vp[3] = 0.0;
	return (vec_norm(&wrld_nrm));
}

t_vcpnt	normal_at(t_obj *obj, t_vcpnt *pnt)
{
	t_vcpnt	wrld_normal;

	if (obj->type == SPHERE)
		wrld_normal = normal_sphere(&obj->data.sp, pnt);
	else if (obj->type == PLANE)
		wrld_normal = normal_pl(&obj->data.pl);
	else
		wrld_normal = normal_cl(&obj->data.cl, pnt);
	return (wrld_normal);
}