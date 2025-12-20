/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:21:47 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 06:00:13 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	lighting(t_material *mat, t_light *light, t_prlgt *l)
{
	double	factor;

	if (l->light_dot_nrm < 0.0)
	{
		l->diffuse = (t_vcpnt){0, 0, 0, 0};
		l->specular = (t_vcpnt){0, 0, 0, 0};
	}
	else
	{
		l->diffuse = vec_scale(&l->eff_clr, l->light_dot_nrm * mat->diffuse);
		l->neg_lightv = vec_scale(&l->lightv_nrm, -1);
		l->reflectiv = vec_reflect(&l->neg_lightv, &l->normv);
		l->reflect_dot_eye = vec_dot(&l->reflectiv, &l->eyev);
		if (l->reflect_dot_eye <= 0)
			l->specular = (t_vcpnt){0, 0, 0, 0};
		else
		{
			factor = pow(l->reflect_dot_eye, mat->shiness);
			l->specular = vec_scale(&light->intens, mat->specular * factor);
		}
	}
	l->res = vec_add(&l->ambient, &l->diffuse);
	l->res = vec_add(&l->res, &l->specular);
	return (l->res);
}

t_light	*create_light(t_vcpnt *pnt, t_vcpnt *color, double ratio)
{
	t_light	*light;

	if (!pnt || !color)
		return (NULL);
	light = malloc(sizeof(t_light));
	if (!light)
		return (NULL);
	light->intens = *color;
	light->pnt_light = *pnt;
	light->ratio = ratio;
	return (light);
}

void	sp_pre_light(t_master *app, t_prlgt *pr, t_light *l)
{
	t_vcpnt	scene_amb;

	scene_amb = vec_scale(&app->amb.color, app->amb.ratio);
	pr->ambient = vec_muls(&scene_amb, &pr->obj->data.sp.mat.color);
	pr->eff_clr = vec_muls(&pr->obj->data.sp.mat.color, &l->intens);
	pr->lightv = vec_subs(&l->pnt_light, &pr->hit_pnt);
	pr->lightv_nrm = vec_norm(&pr->lightv);
	pr->over_pnt = vec_scale(&pr->normv, EPSILON);
	pr->over_pnt = vec_add(&pr->hit_pnt, &pr->over_pnt);
	pr->light_dot_nrm = vec_dot(&pr->lightv_nrm, &pr->normv);
}

void	sp_pre_plane(t_master *app, t_prlgt *pr, t_light *l)
{
	t_vcpnt	scene_amb;

	scene_amb = vec_scale(&app->amb.color, app->amb.ratio);
	pr->ambient = vec_muls(&scene_amb, &pr->obj->data.pl.mat.color);
	pr->eff_clr = vec_muls(&pr->obj->data.pl.mat.color, &l->intens);
	pr->lightv = vec_subs(&l->pnt_light, &pr->hit_pnt);
	pr->lightv_nrm = vec_norm(&pr->lightv);
	pr->over_pnt = vec_scale(&pr->normv, EPSILON);
	pr->over_pnt = vec_add(&pr->hit_pnt, &pr->over_pnt);
	pr->light_dot_nrm = vec_dot(&pr->lightv_nrm, &pr->normv);
}
