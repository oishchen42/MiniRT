/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 07:50:53 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/12 20:56:35 by tdietz-r         ###   ########.fr       */
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
	if (is_shadowed(w, &l->over_pnt))
		return (l->ambient);
	return (lighting(&obj->data.sp.mat, light, l));
}

void	record_hit(t_hit *hit, t_inter *inter, int *pos)
{
	int	i;

	//printf("OUR POS: %d\n", *pos);
	i = -1;
	while (++i < *pos)
	{
		if (inter[i].t >= 0.0 && inter[i].t < hit->min) // do we need it to be >= 0.0 or > 0
		{
			hit->min = inter[i].t;
			//printf("CURRENT min is: %.1f\n", hit->min);
			hit->pos = i;
			//printf("hit->pos is: %d\n", hit->pos);
			hit->obj = inter[i].obj;
			//printf("RECORDED OBJ: %d\n", hit->obj->n);
		}
	}
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
		//printf("THE OBJECT WE ARE WORKING WITH: %d\n", obj->n);
		if (inter_obj(obj, r, inter, &inter_count))
			record_hit(&hit, inter, &inter_count);
		cp_obj = cp_obj->next;
	}
	if (hit.pos != -1)
	{
		pre_light = pre_calc(wrld, &hit, r);
		//printf("we are hree\n");
		t_vcpnt res = shade_hit(wrld, &pre_light);
		return (res);
	}
	return ((t_vcpnt){0,0,0,1});
}
