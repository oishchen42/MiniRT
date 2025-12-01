/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_mtx_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:15:29 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/01 19:36:33 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	mult_mtx4_vcpnt4(t_mtx4 *mtx, t_vcpnt *pnt)
{
	int		i;
	t_vcpnt	res;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		res.vp[i] = (mtx->mtx[i][0] * pnt->vp[0]) +
					(mtx->mtx[i][1] * pnt->vp[1]) +
					(mtx->mtx[i][2] * pnt->vp[2]) +
					(mtx->mtx[i][3] * pnt->vp[3]);
	}
	return (res);
}
