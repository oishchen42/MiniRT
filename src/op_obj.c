/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:32:46 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/14 13:25:16 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

//void	point_light(t_obj *obj, t_vcpnt *pnt, t_vcpnt *intens)
//{
//	//t_obj	figure;

//	//figure = get_obj_type(obj); //delete
//	if (!pnt)
//		obj->data.sp.light.pnt_light = (t_vcpnt){0,0,0,0};
//	else
//		obj->data.sp.light.pnt_light = *pnt;
//	if (!intens)
//		obj->data.sp.light.intens = (t_vcpnt){1,1,1,0};
//	else
//		obj->data.sp.light.intens = *intens;

//}

void	material(t_matirial	*mat)
{
	mat->ambient = 0.2;
	mat->diffuse = 0.0;
	mat->shiness = 200;
	mat->specular = 0.7;
	mat->color = (t_vcpnt){0.3, 0.4, 0.9, 0};
}

t_obj	*sphere(t_matirial *mat, t_vcpnt *orig)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = SPHERE;
	if (orig)
		obj->data.sp.orig = *orig;
	else
		obj->data.sp.orig = (t_vcpnt){0,0,0,1};
	if (!mat)
		material(&obj->data.sp.mat);
	else
		obj->data.sp.mat = *mat;
	get_id_mtx4(&obj->data.sp.transform);
	obj->data.sp.inv_mtx = mtx4_inverse(&obj->data.sp.transform);
	obj->data.sp.tr_inv_mtx = transpose(&obj->data.sp.inv_mtx);
	obj->data.sp.radi = 1.0;
	obj->type = SPHERE;
	return (obj);
}

t_obj	*plane(void)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = PLANE;
	get_id_mtx4(&obj->data.pl.transform);
	obj->data.pl.inv_mtx = mtx4_inverse(&obj->data.pl.transform);
	obj->data.pl.tr_inv_mtx = transpose(&obj->data.pl.inv_mtx);
	obj->data.pl.mat.color = (t_vcpnt){1, 1, 1, 1}; 
	obj->data.pl.mat.ambient = 0.1;
	obj->data.pl.mat.diffuse = 0.9;
	obj->data.pl.mat.specular = 0.1;
	obj->data.pl.mat.shiness = 200;
	return (obj);
}

t_obj	*cylinder(t_matirial *mat, t_vcpnt *orig, double min, double max)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = CYLINDER;
	get_id_mtx4(&obj->data.cl.transform);
	obj->data.cl.inv_mtx = mtx4_inverse(&obj->data.cl.transform);
	obj->data.cl.tr_inv_mtx = transpose(&obj->data.cl.inv_mtx);
	if (orig)
		obj->data.cl.orig = *orig;
	else
		obj->data.cl.orig = (t_vcpnt){0,0,0,1};
	if (!mat)
		material(&obj->data.cl.mat);
	else
		obj->data.cl.mat = *mat;
	obj->data.cl.min = min;
	obj->data.cl.max = max;
	obj->data.cl.is_closed = true;
	return (obj);
}

t_type	get_obj(t_obj *obj)
{
	(void)obj;
	t_type	obj_type;

	//if (obj->type == SPHERE)
	obj_type = SPHERE;
	return (obj_type);
}

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

t_matirial	create_material(t_vcpnt	*color, double diffuse, double specular)
{
	t_matirial	mat;

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
	t_vcpnt local_pnt;
	t_vcpnt local_nrm;
	t_vcpnt wrld_nrm;

	local_pnt = mult_mtx4_vcpnt4(&cl->inv_mtx, world_pnt);
	local_nrm = (t_vcpnt){local_pnt.vp[0], 0, local_pnt.vp[2], 0};
	wrld_nrm = mult_mtx4_vcpnt4(&cl->tr_inv_mtx, &local_nrm);
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

