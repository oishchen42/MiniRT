/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:05:38 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/16 20:20:35 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mtx4	mtx4_ornt(t_vcpnt *left, t_vcpnt *true_up, t_vcpnt *forward)
{
	t_mtx4	mtx;

	get_empty_mtx4(&mtx);
	mtx.mtx[0][0] = left->vp[0];
	mtx.mtx[0][1] = left->vp[1];
	mtx.mtx[0][2] = left->vp[2];
	mtx.mtx[1][0] = true_up->vp[0];
	mtx.mtx[1][1] = true_up->vp[1];
	mtx.mtx[1][2] = true_up->vp[2];
	mtx.mtx[2][0] = -forward->vp[0];
	mtx.mtx[2][1] = -forward->vp[1];
	mtx.mtx[2][2] = -forward->vp[2];
	mtx.mtx[3][3] = 1.0;
	//print_inv4(&mtx);
	return (mtx);
}

void	wadd_obj(t_world *world, t_light *light, t_obj *obj)
{
	t_list	*node;

	if (obj)
	{
		node = ft_lstnew((void *)obj);
		ft_lstadd_back(&world->objs, node);
	}
	if (light)
	{
		node = ft_lstnew((void *)light);
		ft_lstadd_back(&world->lights, node);
	}
}

static t_mtx4	get_orientation_matrix(t_vcpnt *from, t_vcpnt *to, t_vcpnt *up)
{
	t_vcpnt	fwd;
	t_vcpnt	left;
	t_vcpnt	true_up;
	t_vcpnt	up_n;

	fwd = vec_subs(to, from);
	fwd = vec_norm(&fwd);
	up_n = vec_norm(up);
	left = vec_cross(&fwd, &up_n);
	left = vec_norm(&left);
	true_up = vec_cross(&left, &fwd);
	return (mtx4_ornt(&left, &true_up, &fwd));
}

//Timo updated function. To many declarations
t_mtx4	view_transform(t_vcpnt *from, t_vcpnt *to, t_vcpnt *up)
{
	t_mtx4	ornt;
	t_mtx4	trans;
	t_mtx4	res;
	t_vcpnt	neg_from;

	ornt = get_orientation_matrix(from, to, up);
	neg_from = vec_scale(from, -1);
	trans = trans4(&neg_from);
	res = mtxs_mult4(&ornt, &trans);
	return (res);
}

void	camera(t_camera *camera)
{
	camera->half_view = tan(camera->field_of_view / 2);
	camera->aspect = camera->hsize / camera->vsize;
	if (camera->aspect >= 1.0)
	{
		camera->half_width = camera->half_view;
		camera->half_height = camera->half_view / camera->aspect;
	}
	else
	{
		camera->half_width = camera->half_view * camera->aspect;
		camera->half_height = camera->half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
}
