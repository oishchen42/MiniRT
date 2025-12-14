/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:24:24 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/14 02:05:03 by oishchen         ###   ########.fr       */
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
		//printf("t: %.1f\n", t);
		inter->obj = obj;
		inter->count = count;
		inter->t = t;
	}
}

void	call_get_inter(t_obj *obj, double t, t_inter *inter, t_supitr *itr)
{
	itr->bl = true;
	get_inter(obj, 1, t, inter);
}

int	check_cup(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->pnt.vp[0] + t * ray->vec.vp[0];
	z = ray->pnt.vp[2] + t * ray->vec.vp[2];
	return (pow(x, 2.0) + pow(z, 2.0) <= 1);
}

int	inter_cl(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
{
	t_supitr	itr;

	itr.bl = false;
	itr.lcl = ray_transform(ray_orig, &obj->data.cl.inv_mtx);
	itr.a = pow(itr.lcl.vec.vp[0], 2.0) + pow(itr.lcl.vec.vp[2], 2.0);
	if (itr.a < EPSILON)
		return (false);
	itr.b = 2.0 * itr.lcl.pnt.vp[0] * itr.lcl.vec.vp[0] + 2.0 * itr.lcl.pnt.vp[2]
		* itr.lcl.vec.vp[2];
	itr.c = pow(itr.lcl.pnt.vp[0], 2.0) + pow(itr.lcl.pnt.vp[2], 2.0) - 1;
	itr.disc = pow(itr.b, 2.0) - 4 * itr.a * itr.c;
	if (itr.disc < 0)
		return (false);
	itr.t1 = (-itr.b - sqrt(itr.disc)) / (2.0 * itr.a);
	itr.t2 = (-itr.b + sqrt(itr.disc)) / (2.0 * itr.a);
	if (itr.t1 > itr.t2)
		ft_swap(&itr.t1, &itr.t2);
	itr.y0 = itr.lcl.pnt.vp[1] + itr.t1 * itr.lcl.vec.vp[1];
	if (itr.y0 > obj->data.cl.min && itr.y0 < obj->data.cl.max)
		call_get_inter(obj, itr.t1,  &inter[(*count)++], &itr);
	itr.y1 = itr.lcl.pnt.vp[1] + itr.t2 * itr.lcl.vec.vp[1];
	if (itr.y1 > obj->data.cl.min && itr.y1 < obj->data.cl.max)
		call_get_inter(obj, itr.t2, &inter[(*count)++], &itr);
	return (itr.bl);
}

int	inter_sp(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
{
	t_vcpnt		sp_2_ray;
	double		a;
	double		b;
	double		c;
	double		D;
	//t_mtx4		inv_mtx;
	t_ray		local_ray;

	//inv_mtx = mtx4_inverse(&obj->data.sp.transform);
	local_ray = ray_transform(ray_orig, &obj->data.sp.inv_mtx);
	sp_2_ray = vec_subs(&local_ray.pnt, &obj->data.sp.orig);
	a = vec_dot(&local_ray.vec, &local_ray.vec);
	b = vec_dot(&local_ray.vec, &sp_2_ray) * 2.0;
	c = vec_dot(&sp_2_ray, &sp_2_ray) - pow(obj->data.sp.radi, 2.0);
	D = pow(b, 2) - 4.0 * a * c;
	if (D < 0)
		return (false);
	get_inter(obj, 1, (-b - sqrt(D)) / (2.0 * a), &inter[*count]);
	(*count)++;
	get_inter(obj, 1, (-b + sqrt(D)) / (2.0 * a), &inter[*count]);
	(*count)++;
	return (true);
	//printf("OBJ: %d, t1 = %.1f, t2 = %.1f\n", obj->n, inter[*count - 2].t, inter[*count - 1].t);
}

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
