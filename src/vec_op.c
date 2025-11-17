/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 22:11:13 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/16 16:04:19 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vec	vec_sums(t_vec *vec1, t_vec *vec2)
{
	t_vec	vec_res;

	vec_res.x = vec1->x + vec2->x;
	vec_res.y = vec1->y + vec2->y;
	vec_res.z = vec1->z + vec2->z;
	return (vec_res);
}

t_vec	vec_subs(t_vec *vec1, t_vec *vec2)
{
	t_vec	vec_res;

	vec_res.x = vec1->x - vec2->x;
	vec_res.y = vec1->y - vec2->y;
	vec_res.z = vec1->z - vec2->z;
	return (vec_res);
}

t_vec	vec_muls(t_vec *vec1, t_vec *vec2)
{
	t_vec	vec_res;

	vec_res.x = vec1->x - vec2->x;
	vec_res.y = vec1->y - vec2->y;
	vec_res.z = vec1->z - vec2->z;
	return (vec_res);
}

double	vec_mag(t_vec *vec1)
{
	double	mag;

	mag = sqrt(pow(vec1->x, 2) + pow(vec1->y, 2) + pow(vec1->z, 2));
	return (mag);
}

t_vec	vec_norm(t_vec *vec1)
{
	t_vec	norm;
	double	vc_mag;

	vc_mag = vec_mag(vec1);
	norm.x = vec1->x / vc_mag;
	norm.y = vec1->y / vc_mag;
	norm.z = vec1->z / vc_mag;
	return (norm);
}

void	vec_mul(t_vec *vec1, double mul)
{
	vec1->x *= mul;
	vec1->y *= mul;
	vec1->z *= mul;
}

void	vec_div(t_vec *vec1, double divisor)
{
	vec1->x /= divisor;
	vec1->y /= divisor;
	vec1->z /= divisor;
}

double	vec_dot(t_vec *vec1, t_vec *vec2)
{
	double	res;

	res = vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z;
	return (res);
}

t_vec	vec_cross(t_vec *vec1, t_vec *vec2)
{
	t_vec	vec_res;

	vec_res.x = vec1->y * vec2->z - vec1->z * vec2->y;
	vec_res.z = vec1->x * vec2->z - vec1->z * vec2->x;
	vec_res.z = vec1->x * vec2->y - vec1->y * vec2->x;
	return (vec_res);
}
