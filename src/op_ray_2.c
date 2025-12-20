/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:47:58 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 05:32:13 by oishchen         ###   ########.fr       */
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

void	record_t12(t_supitr *itr)
{
	itr->t1 = (-itr->b - sqrt(itr->disc)) / (2.0 * itr->a);
	itr->t2 = (-itr->b + sqrt(itr->disc)) / (2.0 * itr->a);
}

int	inter_sp(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
{
	t_vcpnt	sp_2_ray;
	double	k[4];
	t_ray	local_ray;

	local_ray = ray_transform(ray_orig, &obj->data.sp.inv_mtx);
	sp_2_ray = vec_subs(&local_ray.pnt, &obj->data.sp.orig);
	k[0] = vec_dot(&local_ray.vec, &local_ray.vec);
	k[1] = vec_dot(&local_ray.vec, &sp_2_ray) * 2.0;
	k[2] = vec_dot(&sp_2_ray, &sp_2_ray) - pow(obj->data.sp.radi, 2.0);
	k[3] = pow(k[1], 2) - 4.0 * k[0] * k[2];
	if (k[3] < 0)
		return (false);
	get_inter(obj, 1, (-k[1] - sqrt(k[3])) / (2.0 * k[0]), &inter[*count]);
	(*count)++;
	get_inter(obj, 1, (-k[1] + sqrt(k[3])) / (2.0 * k[0]), &inter[*count]);
	(*count)++;
	return (true);
}
