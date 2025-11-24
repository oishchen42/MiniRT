/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:24:24 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/24 22:26:44 by oishchen         ###   ########.fr       */
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