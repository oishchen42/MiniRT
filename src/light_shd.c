/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:21:47 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/12 21:09:08 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	lighting(t_material *mat, t_light *light, t_prlgt *l)
{
	double	factor;

	//printf("l->light_dot_rnm: %.1f | mat->diffuse: %.1f\n", l->light_dot_nrm, mat->diffuse);
	if (l->light_dot_nrm < 0.0)
	{
		l->diffuse = (t_vcpnt){0,0,0,0};
		l->specular = (t_vcpnt){0,0,0,0};
	}
	else
	{
		//printf("we are here\n\n");
		//printf("l->eff_clr ");
		//print_vpnt4(&l->eff_clr);
		//printf("l->diffuse: ");

		l->diffuse = vec_scale(&l->eff_clr, l->light_dot_nrm * mat->diffuse);

		//print_vpnt4(&l->diffuse);

		l->neg_lightv = vec_scale(&l->lightv_nrm, -1);
		//printf("lightv: ");
		//print_vpnt4(&l->lightv);
		//printf("\n");
		l->reflectiv = vec_reflect(&l->neg_lightv, &l->normv);
		//printf("reflectiv: ");
		//print_vpnt4(&l->reflectiv);
		//printf("\n");
		l->reflect_dot_eye = vec_dot(&l->reflectiv, &l->eyev);
		if (l->reflect_dot_eye <= 0)
			l->specular = (t_vcpnt){0,0,0,0};
		else
		{
			//printf("my reflecti_do_eye : %.1f\n", l->reflect_dot_eye);
			//printf("mat->shiness: %.1f\n", mat->shiness);
			factor = pow(l->reflect_dot_eye, mat->shiness);
			//printf("my factor : %f\n", factor);
			//printf("my material specular: %.1f\n", mat->specular);
			//printf("mat->specular * factor: %f\n", mat->specular * factor);
			l->specular = vec_scale(&light->intens, mat->specular * factor);
			//printf("l->specular: ");
			//print_vpnt4(&l->specular);
		}
	}
	//printf("l->ambient, l->diffuse: ");
	//print_vpnt4(&l->ambient);
	//print_vpnt4(&l->diffuse);
	//printf("l->specular ");
	//print_vpnt4(&l->specular);
	l->res = vec_add(&l->ambient, &l->diffuse);
	l->res = vec_add(&l->res, &l->specular);
	return (l->res);
}


t_vcpnt	alt_lighting(t_material *mat, t_light *light, t_vcpnt *pnt, t_vcpnt *eye, t_vcpnt *nrmvc)
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

t_prlgt	pre_calc(t_world *wrld, t_hit *hit, t_ray *r)
{
	t_prlgt	pre_light;
	t_light	*light;


	light = (t_light *)wrld->lights->content;

	//print_vpnt4(&light->intens);

	//printf("HIT OBJECT: %d\n", hit->obj->n);

	pre_light.t = hit->min;
	pre_light.obj = hit->obj;


	//printf("r_vec norm: ");
	//print_vpnt4(&r->vec);

	pre_light.eyev = vec_scale(&r->vec, -1);
	//pre_light.eyev = (t_vcpnt){0, sqrt(2) / 2, -1 * sqrt(2) / 2, -1};

	//printf("eyev : ");
	//print_vpnt4(&pre_light.eyev);

	pre_light.scaledv = vec_scale(&r->vec, hit->min);
	//printf("hit->min: %.1f\n", hit->min);
	//printf("pre_light.scaledv: ");
	//print_vpnt4(&pre_light.scaledv);

	pre_light.hit_pnt = vec_add(&pre_light.scaledv, &r->pnt);
	//printf("r->pnt: ");
	//print_vpnt4(&r->pnt);
	//printf("pre_light.hit_pnt ");
	//print_vpnt4(&pre_light.hit_pnt);

	pre_light.normv = normal_at(&hit->obj->data.sp, &pre_light.hit_pnt);
	//printf("norm vec: ");
	//print_vpnt4(&pre_light.normv);
	pre_light.is_inside = vec_dot(&pre_light.normv, &pre_light.eyev) < 0;
	if (pre_light.is_inside)
	{
		//printf("WE ARE INSIDE THE OBJ\n");
		pre_light.normv = vec_scale(&pre_light.normv, -1);
	}
	pre_light.eff_clr = vec_muls(&pre_light.obj->data.sp.mat.color, &light->intens);
	pre_light.lightv = vec_subs(&light->pnt_light, &pre_light.hit_pnt);
	pre_light.lightv_nrm = vec_norm(&pre_light.lightv);
	pre_light.over_pnt = vec_scale(&pre_light.normv, EPSILON);
	pre_light.over_pnt = vec_add(&pre_light.hit_pnt, &pre_light.over_pnt);
	pre_light.ambient = vec_scale(&pre_light.eff_clr, pre_light.obj->data.sp.mat.ambient);
	pre_light.light_dot_nrm = vec_dot(&pre_light.lightv_nrm, &pre_light.normv);
	return (pre_light);
}

int	is_inter_shd(t_world *wrld, t_ray *r, double dis)
{
	t_inter	inter[MAX_INTER];
	t_list	*cp_obj = wrld->objs;
	int		inter_count;
	t_obj	*obj;
	t_hit	hit;

	inter_count = 0;
	hit.min = INT_MAX;
	hit.pos = -1;
	while (cp_obj && inter_count < MAX_INTER / 2) // TODO do smth with MAX_INTER
	{
		obj = (t_obj *)cp_obj->content;
		//printf("THE OBJECT WE ARE WORKING WITH: %d\n", obj->n);
		if (inter_obj(obj, r, inter, &inter_count))
			record_hit(&hit, inter, &inter_count);
		cp_obj = cp_obj->next;
	}
	if (hit.pos != -1 && hit.min < dis)
		return (true);
	return (false);
}

int	is_shadowed(t_world *wrld, t_vcpnt *pnt)
{
	t_light	*lg;
	t_vcpnt	dir_natr;
	t_vcpnt	dir;
	t_ray	r;
	double	dis;

	if (wrld->lights)
	{
		lg = (t_light *)wrld->lights->content;
		dir_natr = vec_subs(&lg->pnt_light, pnt);
		dir = vec_norm(&dir_natr);
		dis = vec_mag(&dir_natr);
		r = (t_ray){*pnt, dir};
		if (is_inter_shd(wrld, &r, dis))
			return (true);
	}
	return (false);
}
