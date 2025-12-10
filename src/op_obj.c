/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:32:46 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/10 20:00:37 by oishchen         ###   ########.fr       */
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
t_light	*create_light(t_vcpnt *pnt, t_vcpnt *color)
{
	t_light	*light;

	if (!pnt || !color)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->intens = *color;
	light->pnt_light = *pnt;
	return (light);
}

void	material(t_matirial	*mat)
{
	mat->ambient = 0.1;
	mat->diffuse = 0.9;
	mat->shiness = 200;
	mat->specular = 0.9;
	mat->color = (t_vcpnt){1, 1, 1, 0};
}

t_obj	*sphere(t_matirial *mat, t_vcpnt orig)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (!obj)
		return (NULL);
	obj->type = SPHERE;
	obj->data.sp.orig = orig;
	if (!mat)
		material(&obj->data.sp.mat);
	else
		obj->data.sp.mat = *mat;
	create_transform_mtx4(&obj->data.sp.transform, NULL);
	obj->data.sp.radi = 1.0;
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

void	create_transform_mtx4(t_mtx4 *priv_mtx, t_mtx4 *new_mtx)
{
	if (new_mtx == NULL)
	{
		get_empty_mtx4(priv_mtx);
		priv_mtx->mtx[0][0] = 1.0;
		priv_mtx->mtx[1][1] = 1.0;
		priv_mtx->mtx[2][2] = 1.0;
		priv_mtx->mtx[3][3] = 1.0;
	}
	else
		*priv_mtx = *new_mtx;
}

t_matirial	create_material(t_vcpnt	*color, double diffuse, double specular)
{
	t_matirial	mat;

	mat.color = *color;
	mat.diffuse = diffuse;
	mat.specular = specular;
	return (mat);
}

t_vcpnt	normal_at(t_sphere *sp, t_vcpnt *pnt)
{
	t_vcpnt	std;
	t_vcpnt	obj_pnt;
	t_mtx4	inv_mtx;
	t_mtx4	tr_inv_mtx;
	t_vcpnt	obj_norm;
	t_vcpnt	world_norm;

	std = (t_vcpnt){0,0,0,1};
	inv_mtx = mtx4_inverse(&sp->transform);
	obj_pnt = mult_mtx4_vcpnt4(&inv_mtx, pnt);
	obj_norm = vec_subs(&obj_pnt, &std);
	tr_inv_mtx = transpose(&inv_mtx);
	world_norm = mult_mtx4_vcpnt4(&tr_inv_mtx, &obj_norm);
	world_norm.vp[3] = 0;
	world_norm = vec_norm(&world_norm);
	return (world_norm);
}

t_vcpnt	lighting(t_matirial *mat, t_light *light, t_prlgt *l)
{
	double	factor;

	if (l->light_dot_nrm < 0)
	{
		l->diffuse = (t_vcpnt){0,0,0,0};
		l->specular = (t_vcpnt){0,0,0,0};
	}
	else
	{
		printf("we are here\n\n");
		printf("l->light_dot_rnm: %.1f | mat->diffuse: %.1f\n", l->light_dot_nrm, mat->diffuse);
		printf("l->eff_clr ");
		print_vpnt4(&l->eff_clr);
		printf("l->diffuse: ");

		l->diffuse = vec_scale(&l->eff_clr, l->light_dot_nrm * mat->diffuse);

		print_vpnt4(&l->diffuse);

		l->neg_lightv = vec_scale(&l->lightv_nrm, -1);
		printf("lightv: ");
		print_vpnt4(&l->lightv);
		printf("\n");
		l->reflectiv = vec_reflect(&l->neg_lightv, &l->normv);
		printf("reflectiv: ");
		print_vpnt4(&l->reflectiv);
		printf("\n");
		l->reflect_dot_eye = vec_dot(&l->reflectiv, &l->eyev);
		if (l->reflect_dot_eye <= 0)
			l->specular = (t_vcpnt){0,0,0,0};
		else
		{
			printf("my reflecti_do_eye : %.1f\n", l->reflect_dot_eye);
			printf("mat->shiness: %.1f\n", mat->shiness);
			factor = pow(l->reflect_dot_eye, mat->shiness);
			printf("my factor : %f\n", factor);
			printf("my material specular: %.1f\n", mat->specular);
			printf("mat->specular * factor: %f\n", mat->specular * factor);
			l->specular = vec_scale(&light->intens, mat->specular * factor);
			
			printf("l->specular: ");
			print_vpnt4(&l->specular);
		}
	}
	printf("l->ambient, l->diffuse: ");
	print_vpnt4(&l->ambient);
	print_vpnt4(&l->diffuse);
	printf("l->specular ");
	print_vpnt4(&l->specular);
	l->res = vec_add(&l->ambient, &l->diffuse);
	l->res = vec_add(&l->res, &l->specular);
	return (l->res);
}


t_vcpnt	alt_lighting(t_matirial *mat, t_light *light, t_vcpnt *pnt, t_vcpnt *eye, t_vcpnt *nrmvc)
{
	t_vcpnt	effective_color;
	t_vcpnt	lightv;
	t_vcpnt	ambient;
	double	light_dot_normal;
	double	reflect_dot_eye;
	double	factor;
	t_vcpnt	lightv_natur;
	t_vcpnt	diffuse;
	t_vcpnt	specular;
	t_vcpnt	reflectiv;
	t_vcpnt	neg_lightv;
	t_vcpnt	res;

	effective_color = vec_muls(&mat->color, &light->intens);
	//sub_lgtp_pnt = vec_subs(&light->pnt_light, pnt);
	lightv_natur = vec_subs(&light->pnt_light, pnt);
	lightv = vec_norm(&lightv_natur);
	ambient = vec_scale(&effective_color, mat->ambient);
	light_dot_normal = vec_dot(&lightv, nrmvc);
	if (light_dot_normal < 0)
	{
		diffuse = (t_vcpnt){0,0,0,0};
		specular = (t_vcpnt){0,0,0,0};
	}
	else
	{
		diffuse = vec_scale(&effective_color, light_dot_normal * mat->diffuse);
		neg_lightv = vec_scale(&lightv, -1);
		reflectiv = vec_reflect(&neg_lightv, nrmvc);
		reflect_dot_eye = vec_dot(&reflectiv, eye);
		if (reflect_dot_eye <= 0)
			specular = (t_vcpnt){0,0,0,0};
		else
		{
			factor = pow(reflect_dot_eye, mat->shiness);
			specular = vec_scale(&light->intens, mat->specular * factor);
		}
	}
	res = vec_add(&ambient, &diffuse);
	res = vec_add(&res, &specular);
	return (res);
}