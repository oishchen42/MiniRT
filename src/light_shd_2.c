/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shd_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 19:47:57 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 01:51:20 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	sp_pre_cylinder(t_master *app, t_prlgt *pr, t_light *l)
{
	t_vcpnt scene_amb;

	scene_amb = vec_scale(&app->amb.color, app->amb.ratio);
	pr->eff_clr = vec_muls(&pr->obj->data.cl.mat.color, &l->intens);
	pr->lightv = vec_subs(&l->pnt_light, &pr->hit_pnt);
	pr->lightv_nrm = vec_norm(&pr->lightv);
	pr->over_pnt = vec_scale(&pr->normv, EPSILON);
	pr->over_pnt = vec_add(&pr->hit_pnt, &pr->over_pnt);
	pr->ambient = vec_scale(&pr->eff_clr, pr->obj->data.cl.mat.ambient);
	pr->light_dot_nrm = vec_dot(&pr->lightv_nrm, &pr->normv);
}

t_prlgt	pre_calc(t_master *app, t_hit *hit, t_ray *r)
{
	t_prlgt	pre_light;
	t_light	*light;

	light = (t_light *)app->world.lights->content;
	pre_light.t = hit->min;
	pre_light.obj = hit->obj;
	pre_light.eyev = vec_scale(&r->vec, -1);
	pre_light.scaledv = vec_scale(&r->vec, hit->min);
	pre_light.hit_pnt = vec_add(&pre_light.scaledv, &r->pnt);
	pre_light.normv = normal_at(hit->obj, &pre_light.hit_pnt);
	pre_light.is_inside = vec_dot(&pre_light.normv, &pre_light.eyev) < 0;
	if (pre_light.is_inside)
	{
		pre_light.normv = vec_scale(&pre_light.normv, -1);
	}
	if (pre_light.obj->type == SPHERE)
		sp_pre_light(app, &pre_light, light);
	else if (pre_light.obj->type == PLANE)
		sp_pre_plane(app, &pre_light, light);
	else
		sp_pre_cylinder(app, &pre_light, light);
	return (pre_light);
}

int	is_inter_shd(t_world *wrld, t_ray *r, double dis)
{
	t_inter	inter[MAX_INTER];
	t_list	*cp_obj;
	int		inter_count;
	t_obj	*obj;
	t_hit	hit;

	inter_count = 0;
	cp_obj = wrld->objs;
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

//Timo updated function: disected "r = (t_ray){*pnt, dir};"
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
		r.pnt = *pnt;
		r.vec = dir;
		if (is_inter_shd(wrld, &r, dis))
			return (true);
	}
	return (false);
}

t_material	init_mat()
{
	t_material	mat;

	mat.ambient = 0.9;
	mat.diffuse = 0.7;
	mat.specular = 0.7;
	mat.shiness = 200.0;
	return (mat);
}
