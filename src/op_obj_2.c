/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:50:09 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 16:51:32 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	create_transform_mtx4(t_obj *obj, t_mtx4 *new_mtx)
{
	if (obj->type == SPHERE)
	{
		obj->data.sp.transform = *new_mtx;
		obj->data.sp.inv_mtx = mtx4_inverse(&obj->data.sp.transform);
		obj->data.sp.tr_inv_mtx = transpose(&obj->data.sp.inv_mtx);
	}
	else if (obj->type == PLANE)
	{
		obj->data.pl.transform = *new_mtx;
		obj->data.pl.inv_mtx = mtx4_inverse(&obj->data.pl.transform);
		obj->data.pl.tr_inv_mtx = transpose(&obj->data.pl.inv_mtx);
	}
	else
	{
		obj->data.cl.transform = *new_mtx;
		obj->data.cl.inv_mtx = mtx4_inverse(&obj->data.cl.transform);
		obj->data.cl.tr_inv_mtx = transpose(&obj->data.cl.inv_mtx);
	}
}

t_material	create_material(t_vcpnt	*color, double diffuse, double specular)
{
	t_material	mat;

	mat.color = *color;
	mat.diffuse = diffuse;
	mat.specular = specular;
	return (mat);
}

t_vcpnt	normal_sphere(t_sphere *obj, t_vcpnt *pnt)
{
	t_vcpnt	local;
	t_vcpnt	local_nrm;
	t_vcpnt	wrld_nrm;

	local = mult_mtx4_vcpnt4(&obj->inv_mtx, pnt);
	local_nrm = vec_subs(&local, &((t_vcpnt){0, 0, 0, 1}));
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

t_vcpnt	normal_cl(t_cl *cl, t_vcpnt *world_pnt)
{
	t_vcpnt	local_pnt;
	t_vcpnt	local_nrm;
	t_vcpnt	wrld_nrm;

	local_pnt = mult_mtx4_vcpnt4(&cl->inv_mtx, world_pnt);
	local_nrm = (t_vcpnt){local_pnt.vp[0], 0, local_pnt.vp[2], 0};
	wrld_nrm = mult_mtx4_vcpnt4(&cl->tr_inv_mtx, &local_nrm);
	return (vec_norm(&wrld_nrm));
}
