/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:51:14 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 16:51:37 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_vcpnt	normal_at(t_obj *obj, t_vcpnt *pnt)
{
	t_vcpnt	wrld_normal;

	if (obj->type == SPHERE)
		wrld_normal = normal_sphere(&obj->data.sp, pnt);
	else if (obj->type == PLANE)
		wrld_normal = normal_pl(&obj->data.pl);
	else
		wrld_normal = normal_cl(&obj->data.cl, pnt);
	return (wrld_normal);
}
