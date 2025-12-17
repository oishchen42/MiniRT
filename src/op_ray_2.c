/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:47:58 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 16:48:11 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	inter_pl(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
{
	double	t;
	t_ray	local_ray;

	local_ray = ray_transform(ray_orig, &obj->data.pl.inv_mtx);
	if (fabs(local_ray.vec.vp[1]) < EPSILON)
		return (0);
	t = -local_ray.pnt.vp[1] / local_ray.vec.vp[1];
	get_inter(obj, 1, t, &inter[*count]);
	(*count)++;
	return (true);
}

int	inter_obj(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
{
	if (obj->type == SPHERE)
		return (inter_sp(obj, ray_orig, inter, count));
	else if (obj->type == PLANE)
		return (inter_pl(obj, ray_orig, inter, count));
	else
		return (inter_cl(obj, ray_orig, inter, count));
	return (0);
}

t_ray	ray_transform(t_ray *ray, t_mtx4 *mtx)
{
	t_ray	res;

	res.pnt = mult_mtx4_vcpnt4(mtx, &ray->pnt);
	res.vec = mult_mtx4_vcpnt4(mtx, &ray->vec);
	return (res);
}

//t_inter	*hit(t_intersec *list) // TOdO
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
// TOdO : HIT FUNCTION that sotres the hit object
