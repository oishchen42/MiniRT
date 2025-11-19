/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:11:13 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/19 22:22:35 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	vec_add(t_vcpnt *vec1, t_vcpnt *vec2)
{
	t_vcpnt res;

	res.vp[0] = vec1->vp[0] + vec2->vp[0];
	res.vp[1] = vec1->vp[1] + vec2->vp[1];
	res.vp[2] = vec1->vp[2] + vec2->vp[2];
	res.vp[3] = vec1->vp[3] + vec2->vp[3];
	return (res);
}

t_vcpnt	vec_subs(t_vcpnt *vec1, t_vcpnt *vec2)
{
	t_vcpnt res;

	res.vp[0] = vec1->vp[0] - vec2->vp[0];
	res.vp[1] = vec1->vp[1] - vec2->vp[1];
	res.vp[2] = vec1->vp[2] - vec2->vp[2];
	res.vp[3] = vec1->vp[3] - vec2->vp[3];
	return (res);
}

t_vcpnt	vec_muls(t_vcpnt *vec1, t_vcpnt *vec2)
{
	t_vcpnt res;

	res.vp[0] = vec1->vp[0] * vec2->vp[0];
	res.vp[1] = vec1->vp[1] * vec2->vp[1];
	res.vp[2] = vec1->vp[2] * vec2->vp[2];
	res.vp[3] = vec1->vp[3] * vec2->vp[3];
	return (res);
}

double	vec_mag(t_vcpnt *vec)
{
	double mag;

	mag = sqrt(pow(vec->vp[0], 2) + pow(vec->vp[1], 2) +
	pow(vec->vp[2], 2));
	return (mag);
}

t_vcpnt	vec_norm(t_vcpnt *vec)
{
	t_vcpnt	res;
	double	mag;

	mag = vec_mag(vec);
	if (mag == 0)
		return (*vec); 
	res.vp[0] = vec->vp[0] / mag;
	res.vp[1] = vec->vp[1] / mag;
	res.vp[2] = vec->vp[2] / mag;
	res.vp[3] = vec->vp[3];
	return (res);
}

t_vcpnt	vec_scale(t_vcpnt *vec, double scale)
{
	t_vcpnt res;

	res.vp[0] = vec->vp[0] * scale;
	res.vp[1] = vec->vp[1] * scale;
	res.vp[2] = vec->vp[2] * scale;
	res.vp[3] = vec->vp[3] * scale;
	return (res);
}

void	vec_div(t_vcpnt *vec, double divisor)
{
	t_vcpnt res;

	res.vp[0] = vec->vp[0] / divisor;
	res.vp[1] = vec->vp[1] / divisor;
	res.vp[2] = vec->vp[2] / divisor;
	res.vp[3] = vec->vp[3] / divisor;
}

double	vec_dot(t_vcpnt *vec1, t_vcpnt *vec2)
{
	double res;

		res = (vec1->vp[0] * vec2->vp[0]) +
			(vec1->vp[1] * vec2->vp[1]) +
			(vec1->vp[2] * vec2->vp[2]);
	return (res);
}

t_vcpnt	vec_cross(t_vcpnt *vec1, t_vcpnt *vec2)
{
	t_vcpnt res;

	res.vp[0] = vec1->vp[1] * vec2->vp[2] - vec1->vp[2] * vec2->vp[1];
	res.vp[1] = vec1->vp[2] * vec2->vp[0] - vec1->vp[0] * vec2->vp[2];
	res.vp[2] = vec1->vp[0] * vec2->vp[1] - vec1->vp[1] * vec2->vp[0];
	res.vp[3] = 0;
	return (res);
}
