/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:37:51 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/19 22:42:02 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minirt.h>

t_mtx	*translation(t_vcpnt *point)
{
	t_mtx	*res;

	res = malloc(sizeof(t_mtx));
	if (!res)
		return (NULL);
	res[0][3] = point->x;
	res[1][3] = point->y;
	res[2][3] = point->z;
	return (res);
}

//int	intersect(t_vcpnt *point, t_vcpnt *vec)
//{
	
//}

t_vcpnt	tuple_mul(t_mtx4 *mtx1, t_vcpnt *tpl)
{
	t_vcpnt	res;
	int		i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		res.vp[i] = 0;
		j = -1;
		while (++j < 4)
		{
			res.vp[i] += mtx1->mtx[i][j] * tpl->vp[i];
		}
	}
	return (res);
}
