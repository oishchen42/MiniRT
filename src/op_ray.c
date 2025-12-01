/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:24:24 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/29 20:57:10 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_intersec	*get_inter(t_obj *obj, int count, double t)
{
	t_intersec *node;

	node = malloc(sizeof(t_intersec));
	if (!node)
		return (NULL);
	if (count == 0)
	{
		node->obj = obj;
		node->count = count;
		node->next = NULL;
	}
	else
	{
		node->obj = obj;
		node->count = count;
		node->next = NULL;
		node->t = t;
	}
	return (node);
}

void	free_inter(t_intersec *inter)
{
	if (!inter)
		return ;
	inter->obj = NULL;
	inter->count = 0;
	inter->next = NULL;
	inter->t = 0;
	free(inter);
}

t_vcpnt	mv_pnt(t_vcpnt *pnt, t_vcpnt *vec, int t)
{
	t_vcpnt	res;

	res.vp[0] = pnt->vp[0] + vec->vp[0] * (double)t;
	res.vp[1] = pnt->vp[1] + vec->vp[1] * (double)t;
	res.vp[2] = pnt->vp[2] + vec->vp[2] * (double)t;
	return (res);
}

t_intersec	*inter_sp(t_obj *obj, t_ray *ray_orig, t_intersec *inter)
{
	t_vcpnt		sp_2_ray;
	double		a;
	double		b;
	double		c;
	double		D;
	t_mtx4		inv_mtx;
	t_ray		local_ray;

	inv_mtx = mtx4_inverse(&obj->data.sp.transform);
	local_ray = ray_transform(ray_orig, &inv_mtx);
	sp_2_ray = vec_subs(&local_ray.pnt, &obj->data.sp.orig);
	a = vec_dot(&local_ray.vec, &local_ray.vec);
	b = vec_dot(&local_ray.vec, &sp_2_ray) * 2.0;
	c = vec_dot(&sp_2_ray, &sp_2_ray) - pow(obj->data.sp.radi, 2.0);
	D = pow(b, 2) - 4.0 * a * c;
	if (D < 0)
		return (get_inter(obj, 0, 0));
	inter = get_inter(obj, 1, (-b - sqrt(D)) / (2.0 * a));
	if (!inter)
		return (NULL);
	inter->next = get_inter(obj, 1, (-b + sqrt(D)) / (2.0 * a));
	if (!inter->next)
		return (free_inter(inter), NULL);
	return (inter);
}

t_intersec	*inter_obj(t_obj *obj, t_ray *ray_orig)
{
	t_intersec	*res;
	//t_list		*new;

	//if (obj->type == SPHERE)
	//new = ft_lstnew(obj);
	//if (!inter_list)
	//	inter_list = new;
	//else
	//	ft_lstadd_back(&inter_list, new);
	// TODO: Improve logic
	res = NULL;
	res = inter_sp(obj, ray_orig, res);
	return (res);
}

t_ray	ray_transform(t_ray *ray, t_mtx4 *mtx)
{
	t_ray	res;

	res.pnt = mult_mtx4_vcpnt4(mtx, &ray->pnt);
	res.vec = mult_mtx4_vcpnt4(mtx, &ray->vec);
	return (res);
}

t_intersec	*hit(t_intersec *list)
{
	t_intersec *winner = NULL;
	t_intersec *curr = list;

	while (curr)
	{
		if (curr->count > 0 && curr->t > 0) // Valid, positive hit
		{
			if (winner == NULL || curr->t < winner->t)
				winner = curr;
		}
		curr = curr->next;
	}
	return (winner);
}
// TODO : HIT FUNCTION that sotres the hit object
