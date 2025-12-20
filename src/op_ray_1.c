/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:24:24 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 05:32:16 by oishchen         ###   ########.fr       */
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

int	check_cap(t_ray *ray, double t)
{
	double	x;
	double	z;

	x = ray->pnt.vp[0] + t * ray->vec.vp[0];
	z = ray->pnt.vp[2] + t * ray->vec.vp[2];
	return (pow(x, 2.0) + pow(z, 2.0) <= 1);
}

void	inter_cap(t_obj *cl, t_ray *r, t_inter *i, int *count)
{
	double	t;

	if (cl->data.cl.is_closed != true || fabs(r->vec.vp[1]) < EPSILON)
		return ;
	t = (cl->data.cl.min - r->pnt.vp[1]) / r->vec.vp[1];
	if (check_cap(r, t))
	{
		get_inter(cl, 1, t, &i[*count]);
		(*count)++;
	}
	t = (cl->data.cl.max - r->pnt.vp[1]) / r->vec.vp[1];
	if (check_cap(r, t))
	{
		get_inter(cl, 1, t, &i[*count]);
		(*count)++;
	}
}

int	inter_cl(t_obj *obj, t_ray *ray_orig, t_inter *inter, int *count)
{
	t_supitr	itr;

	itr.bl = false;
	itr.lcl = ray_transform(ray_orig, &obj->data.cl.inv_mtx);
	itr.a = pow(itr.lcl.vec.vp[0], 2.0) + pow(itr.lcl.vec.vp[2], 2.0);
	if (itr.a < EPSILON)
		return (inter_cap(obj, &itr.lcl, inter, count), false);
	itr.b = 2.0 * itr.lcl.pnt.vp[0] * itr.lcl.vec.vp[0]
		+ 2.0 * itr.lcl.pnt.vp[2]
		* itr.lcl.vec.vp[2];
	itr.c = pow(itr.lcl.pnt.vp[0], 2.0) + pow(itr.lcl.pnt.vp[2], 2.0) - 1;
	itr.disc = pow(itr.b, 2.0) - 4 * itr.a * itr.c;
	if (itr.disc < 0)
		return (false);
	record_t12(&itr);
	if (itr.t1 > itr.t2)
		ft_swap(&itr.t1, &itr.t2);
	itr.y0 = itr.lcl.pnt.vp[1] + itr.t1 * itr.lcl.vec.vp[1];
	if (itr.y0 > obj->data.cl.min && itr.y0 < obj->data.cl.max)
		call_get_inter(obj, itr.t1, &inter[(*count)++], &itr);
	itr.y1 = itr.lcl.pnt.vp[1] + itr.t2 * itr.lcl.vec.vp[1];
	if (itr.y1 > obj->data.cl.min && itr.y1 < obj->data.cl.max)
		call_get_inter(obj, itr.t2, &inter[(*count)++], &itr);
	inter_cap(obj, &itr.lcl, inter, count);
	return (itr.bl);
}
