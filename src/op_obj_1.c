/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:32:46 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/19 02:56:39 by oishchen         ###   ########.fr       */
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

void	material(t_material	*mat)
{
	mat->ambient = 0.2;
	mat->diffuse = 0.0;
	mat->shiness = 200;
	mat->specular = 0.7;
	mat->color = (t_vcpnt){0.3, 0.4, 0.9, 0};
}

t_obj	*sphere(t_vcpnt *clr)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = SPHERE;
	obj->data.sp.orig = (t_vcpnt){0, 0, 0, 1};
	obj->data.sp.mat = init_mat();
	obj->data.sp.mat.color = *clr;
	get_id_mtx4(&obj->data.sp.transform);
	obj->data.sp.inv_mtx = mtx4_inverse(&obj->data.sp.transform);
	obj->data.sp.tr_inv_mtx = transpose(&obj->data.sp.inv_mtx);
	obj->data.sp.radi = 1.0;
	obj->type = SPHERE;
	return (obj);
}

t_obj	*plane(t_vcpnt *clr)
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
	obj->data.pl.mat.color = *clr;
	return (obj);
}

t_obj	*cylinder(t_vcpnt *clr, t_vcpnt *orig, double min, double max)
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
		obj->data.cl.orig = (t_vcpnt){0, 0, 0, 1};
	obj->data.cl.mat = init_mat();
	obj->data.cl.mat.color = *clr;
	obj->data.cl.min = min;
	obj->data.cl.max = max;
	obj->data.cl.is_closed = true;
	return (obj);
}

t_type	get_obj(t_obj *obj)
{
	t_type	obj_type;

	(void)obj;
	//if (obj->type == SPHERE)
	obj_type = SPHERE;
	return (obj_type);
}
