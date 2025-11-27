/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:32:46 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/27 19:08:23 by oishchen         ###   ########.fr       */
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
