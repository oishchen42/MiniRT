/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:24:24 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/08 22:42:57 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	get_inter(t_obj *obj, int count, double t, t_inter *inter)
{
	if (count == 0)
	{
		inter->obj = obj;
		inter->t = -1;
		inter->count = count;
	}
	else
	{
		printf("tis %.1f\n", t);
		printf("\n");
		inter->obj = obj;
		inter->count = count;
		inter->t = t;
	}
}

void	inter_sp(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
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
	{
		(get_inter(obj, 0, 0, &inter[*count]));
		(*count)++;
		return ;
	}
	get_inter(obj, 1, (-b - sqrt(D)) / (2.0 * a), &inter[*count]);
	(*count)++;
	get_inter(obj, 1, (-b + sqrt(D)) / (2.0 * a), &inter[*count]);
	(*count)++;
}

void	inter_obj(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
{
	//t_list		*new;

	//if (obj->type == SPHERE)
	//new = ft_lstnew(obj);
	//if (!inter_list)
	//	inter_list = new;
	//else
	//	ft_lstadd_back(&inter_list, new);
	// TODO: Improve logic
	inter_sp(obj, ray_orig, inter, count);
}

t_ray	ray_transform(t_ray *ray, t_mtx4 *mtx)
{
	t_ray	res;

	res.pnt = mult_mtx4_vcpnt4(mtx, &ray->pnt);
	res.vec = mult_mtx4_vcpnt4(mtx, &ray->vec);
	return (res);
}

//t_inter	*hit(t_intersec *list) // TODO
//{
//	t_intersec *winner = NULL;
//	t_intersec *curr = list;

//	while (curr)
//	{
//		if (curr->count > 0 && curr->t > 0)
//		{
//			if (winner == NULL || curr->t < winner->t)
//				winner = curr;
//		}
//		curr = curr->next;
//	}
//	return (winner);
//}
// TODO : HIT FUNCTION that sotres the hit object
