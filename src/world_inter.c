/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 07:50:53 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/13 21:11:46 by oishchen         ###   ########.fr       */
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
	if (obj->type == SPHERE)
		return (lighting(&obj->data.sp.mat, light, l));
	else
		return (lighting(&obj->data.pl.mat, light, l));
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

//int	main()
//{
//	t_obj	*cl;
//	t_world	wrld;
//	t_light	*light;
//	t_vcpnt l_pnt;
//	t_vcpnt	l_intens;

//	wrld = init_world();
//	l_pnt = (t_vcpnt){10, 10, -10, 1};
//	l_intens = (t_vcpnt){1, 1, 1, 1};
//	light = create_light(&l_pnt, &l_intens);
//	wadd_obj(&wrld, light, NULL);

//	cl = cylinder(NULL, NULL);
//	wadd_obj(&wrld, NULL, cl);
//	t_ray r;
//	t_vcpnt	orig = {0.5, 0, -5, 1};
//	t_vcpnt	vec = {0.1, 1, 1, 1};

//	vec = vec_norm(&vec);
//	r = (t_ray){orig, vec};
//	world_inter(&wrld, &r);
//}