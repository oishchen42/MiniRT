/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:24:24 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/27 18:17:20 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	mv_pnt(t_vcpnt *pnt, t_vcpnt *vec, int t)
{
	t_vcpnt	res;

	res.vp[0] = pnt->vp[0] + vec->vp[0] * (double)t;
	res.vp[1] = pnt->vp[1] + vec->vp[1] * (double)t;
	res.vp[2] = pnt->vp[2] + vec->vp[2] * (double)t;
	return (res);
}

t_intersec	inter_sp(t_sphere *sphere, t_ray *ray_orig)
{
	t_vcpnt		sp_2_ray;
	double		a;
	double		b;
	double		c;
	double		D;
	t_mtx4		inv_mtx;
	t_ray		local_ray;
	t_intersec	res;

	inv_mtx = mtx4_inverse(&sphere->transform);
	local_ray = ray_transform(ray_orig, &inv_mtx);
	sp_2_ray = vec_subs(&local_ray.pnt, &sphere->orig);
	a = vec_dot(&local_ray.vec, &local_ray.vec);
	b = vec_dot(&local_ray.vec, &sp_2_ray) * 2.0;
	c = vec_dot(&sp_2_ray, &sp_2_ray) - pow(sphere->radi, 2.0);
	res.count = 0;
	res.obj = SPHERE;
	D = pow(b, 2) - 4.0 * a * c;
	if (D < 0)
		return (res);
	res.count = 2;
	res.inter[0] = (-b - sqrt(D)) / (2.0 * a);
	res.inter[1] = (-b + sqrt(D)) / (2.0 * a);
	return (res);
}

t_intersec	inter_obj(t_obj *obj, t_ray *ray_orig)
{
	t_intersec	res;
	//t_list		*new;

	//if (obj->type == SPHERE)
	//new = ft_lstnew(obj);
	//if (!inter_list)
	//	inter_list = new;
	//else
	//	ft_lstadd_back(&inter_list, new);
	// TODO: Improve logic
	res = inter_sp(&obj->data.sp, ray_orig);
	return (res);
}

t_ray	ray_transform(t_ray *ray, t_mtx4 *mtx)
{
	t_ray	res;

	res.pnt = mult_mtx4_vcpnt4(mtx, &ray->pnt);
	res.vec = mult_mtx4_vcpnt4(mtx, &ray->vec);
	return (res);
}

t_intersec	*hit(t_list *inter_list)
{
	t_intersec	*current;
	t_intersec	*res;
	//double		min;
	t_list		*list_cpy;

	current = (t_intersec *)inter_list->content;
	res = NULL;
	list_cpy = inter_list;
	while (list_cpy)
	{
		current = (t_intersec *)list_cpy->content;
		if (!res)
			res = current;
		if (current->count > 0)
		{
			if ((current->inter[0] > 0 || current->inter[1] > 0) &&
			current->inter[0] < res->inter[0] && current->inter[1] < res->inter[1])
				res = current;
		}
		list_cpy = list_cpy->next;
	}
	return (res);
}
// TODO : HIT FUNCTION that sotres the hit object
