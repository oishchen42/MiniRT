/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 07:50:53 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/09 12:46:19 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	shade_hit(t_world *w, t_prlgt *l)
{
	t_obj	*obj;
	t_light	*light;

	//obj = get_obj(w);
	obj = l->obj;
	light = (t_light *)w->lights->content;
	printf("light->intens ");
	print_vpnt4(&light->intens);
	l->eff_clr = vec_muls(&obj->data.sp.mat.color, &light->intens);
	l->lightv = vec_subs(&light->pnt_light, &l->hit_pnt);
	l->lightv_nrm = vec_norm(&l->lightv);
	l->ambient = vec_scale(&l->eff_clr, obj->data.sp.mat.ambient);
	l->light_dot_nrm = vec_dot(&l->lightv_nrm, &l->normv);
	return (lighting(&obj->data.sp.mat, light, l));
	//return (alt_lighting(&obj->data.sp.mat, light, &l->hit_pnt, &l->eyev, &l->normv));
}

void	record_hit(t_hit *hit, t_inter *inter, int *pos)
{
	int	i;

	printf("OUR POS: %d\n", *pos);
	i = -1;
	while (++i < *pos)
	{
		if (inter[i].t > 0.0 && inter[i].t < hit->min)
		{
			hit->min = inter[i].t;
			printf("CURRENT min is: %.1f\n", hit->min);
			hit->pos = i;
			hit->obj = inter[i].obj;
			printf("RECORDED OBJ: %d\n", hit->obj->n);
		}
	}
}

t_prlgt	pre_calc(t_hit *hit, t_ray *r)
{
	t_prlgt	pre_light;

	printf("HIT OBJECT: %d\n", hit->obj->n);
	pre_light.t = hit->min;
	pre_light.obj = hit->obj;

	printf("r_vec norm: ");
	print_vpnt4(&r->vec);

	pre_light.eyev = vec_scale(&r->vec, -1);

	printf("eyev : ");
	print_vpnt4(&pre_light.eyev);

	pre_light.scaledv = vec_scale(&r->vec, hit->min);
	printf("hit->min: %.1f\n", hit->min);
	printf("pre_light.scaledv: ");
	print_vpnt4(&pre_light.scaledv);

	pre_light.hit_pnt = vec_add(&pre_light.scaledv, &r->pnt);
	printf("r->pnt: ");
	print_vpnt4(&r->pnt);
	printf("pre_light.hit_pnt ");
	print_vpnt4(&pre_light.hit_pnt);

	pre_light.normv = normal_at(&hit->obj->data.sp, &pre_light.hit_pnt);
	printf("norm vec: ");
	print_vpnt4(&pre_light.normv);
	pre_light.is_inside = vec_dot(&pre_light.normv, &pre_light.eyev) < 0;
	if (pre_light.is_inside)
	{
		printf("WE ARE INSIDE THE OBJ\n");
		pre_light.normv = vec_scale(&pre_light.normv, -1);
	}
	return (pre_light);
}

t_vcpnt	world_inter(t_world *wrld, t_ray *r)
{
	t_inter	inter[MAX_INTER];
	t_list	*cp_obj = wrld->objs;
	int		inter_count;
	t_obj	*obj;
	t_hit	hit;
	t_prlgt	pre_light;

	inter_count = 0;
	hit.min = INT_MAX;
	hit.pos = -1;
	while (cp_obj && inter_count < MAX_INTER / 2) // TODO do smth with MAX_INTER
	{
		obj = (t_obj *)cp_obj->content;
		printf("THE OBJECT WE ARE WORKING WITH: %d\n", obj->n);
		inter_obj(obj, r, inter, &inter_count);
		cp_obj = cp_obj->next;
		record_hit(&hit, inter, &inter_count);
	}
	if (hit.pos != -1)
	{
		pre_light = pre_calc(&hit, r);
		//printf("we are hree\n");
		t_vcpnt res = shade_hit(wrld, &pre_light);
		return (res);
	}
	return ((t_vcpnt){0,0,0,1});
}
