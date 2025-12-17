/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shd_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:21:47 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/16 21:17:56 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	lighting(t_material *mat, t_light *light, t_prlgt *l)
{
	double	factor;

	//printf("l->light_dot_rnm: %.1f | mat->diffuse: %.1f\n", l->light_dot_nrm, mat->diffuse);
	if (l->light_dot_nrm < 0.0)
	{
		l->diffuse = (t_vcpnt){0, 0, 0, 0};
		l->specular = (t_vcpnt){0, 0, 0, 0};
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
			l->specular = (t_vcpnt){0, 0, 0, 0};
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

void	sp_pre_light(t_prlgt *pr, t_light *l)
{
	pr->eff_clr = vec_muls(&pr->obj->data.sp.mat.color, &l->intens);
	pr->lightv = vec_subs(&l->pnt_light, &pr->hit_pnt);
	pr->lightv_nrm = vec_norm(&pr->lightv);
	pr->over_pnt = vec_scale(&pr->normv, EPSILON);
	pr->over_pnt = vec_add(&pr->hit_pnt, &pr->over_pnt);
	pr->ambient = vec_scale(&pr->eff_clr, pr->obj->data.sp.mat.ambient);
	pr->light_dot_nrm = vec_dot(&pr->lightv_nrm, &pr->normv);
}

void	sp_pre_plane(t_prlgt *pr, t_light *l)
{
	pr->eff_clr = vec_muls(&pr->obj->data.pl.mat.color, &l->intens);
	pr->lightv = vec_subs(&l->pnt_light, &pr->hit_pnt);
	pr->lightv_nrm = vec_norm(&pr->lightv);
	pr->over_pnt = vec_scale(&pr->normv, EPSILON);
	pr->over_pnt = vec_add(&pr->hit_pnt, &pr->over_pnt);
	pr->ambient = vec_scale(&pr->eff_clr, pr->obj->data.pl.mat.ambient);
	pr->light_dot_nrm = vec_dot(&pr->lightv_nrm, &pr->normv);
}
