/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:13:50 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 05:14:20 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	vec_scale(t_vcpnt *vec, double scale)
{
	t_vcpnt	res;

	res.vp[0] = vec->vp[0] * scale;
	res.vp[1] = vec->vp[1] * scale;
	res.vp[2] = vec->vp[2] * scale;
	res.vp[3] = 0;
	return (res);
}

void	vec_div(t_vcpnt *vec, double divisor)
{
	vec->vp[0] = vec->vp[0] / divisor;
	vec->vp[1] = vec->vp[1] / divisor;
	vec->vp[2] = vec->vp[2] / divisor;
}

double	vec_dot(t_vcpnt *vec1, t_vcpnt *vec2)
{
	double	res;

	res = (vec1->vp[0] * vec2->vp[0])
		+ (vec1->vp[1] * vec2->vp[1])
		+ (vec1->vp[2] * vec2->vp[2]);
	return (res);
}

t_vcpnt	vec_cross(t_vcpnt *vec1, t_vcpnt *vec2)
{
	t_vcpnt	res;

	res.vp[0] = vec1->vp[1] * vec2->vp[2] - vec1->vp[2] * vec2->vp[1];
	res.vp[1] = vec1->vp[2] * vec2->vp[0] - vec1->vp[0] * vec2->vp[2];
	res.vp[2] = vec1->vp[0] * vec2->vp[1] - vec1->vp[1] * vec2->vp[0];
	res.vp[3] = 0;
	return (res);
}

t_vcpnt	vec_reflect(t_vcpnt *in, t_vcpnt *norm)
{
	double	vecs_dt;
	t_vcpnt	vecs_dt2;
	t_vcpnt	res;

	vecs_dt = vec_dot(in, norm);
	vecs_dt2 = vec_scale(norm, vecs_dt * 2.0);
	res = vec_subs(in, &vecs_dt2);
	return (res);
}
