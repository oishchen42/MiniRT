/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:32:46 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/01 21:55:13 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_obj	sphere(void)
{
	t_obj	obj;
	
	obj.type = SPHERE;
	obj.data.sp.orig = (t_vcpnt){0, 0, 0, 1};
	printf("no corruptinon\n"); // delete
	create_transform_mtx4(&obj.data.sp.transform, NULL);
	printf("no corruptinon\n"); // delete
	obj.data.sp.radi = 1.0;
	return (obj);
}

t_type	get_obj(t_obj *obj)
{
	(void)obj;
	t_type	obj_type;

	//if (obj->type == SPHERE)
	obj_type = SPHERE;
	return (obj_type);
}

void	create_transform_mtx4(t_mtx4 *priv_mtx, t_mtx4 *new_mtx)
{
	if (new_mtx == NULL)
	{
		get_empty_mtx4(priv_mtx);
		priv_mtx->mtx[0][0] = 1.0;
		priv_mtx->mtx[1][1] = 1.0;
		priv_mtx->mtx[2][2] = 1.0;
		priv_mtx->mtx[3][3] = 1.0;
	}
	else
		*priv_mtx = *new_mtx;
}

t_vcpnt	normal_at(t_sphere *sp, t_vcpnt *pnt)
{
	t_vcpnt	std;
	t_vcpnt	obj_pnt;
	t_mtx4	inv_mtx;
	t_mtx4	tr_inv_mtx;
	t_vcpnt	obj_norm;
	t_vcpnt	world_norm;

	std = (t_vcpnt){0,0,0,1};
	inv_mtx = mtx4_inverse(&sp->transform);
	obj_pnt = mult_mtx4_vcpnt4(&inv_mtx, pnt);
	obj_norm = vec_subs(&obj_pnt, &std);
	tr_inv_mtx = transpose(&inv_mtx);
	world_norm = mult_mtx4_vcpnt4(&tr_inv_mtx, &obj_norm);
	return (world_norm);
}
