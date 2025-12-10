/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 18:05:38 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/10 16:21:23 by oishchen         ###   ########.fr       */
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
	print_inv4(&mtx);
	return (mtx);
}

t_mtx4	view_transform(t_vcpnt *from, t_vcpnt *to, t_vcpnt *up)
{
	t_vcpnt	forward = vec_subs(to, from);
	forward = vec_norm(&forward);
	t_vcpnt	up_norm = vec_norm(up);
	t_vcpnt	left = vec_cross(&forward, &up_norm);
	t_vcpnt	true_up = vec_cross(&left, &forward);
	t_mtx4	ornt_mtx4 = mtx4_ornt(&left, &true_up, &forward);
	t_vcpnt	neg_from = vec_scale(from, -1);
	t_mtx4	mtx4_trans = trnas4(&neg_from);
	t_mtx4	res = mtxs_mult4(&ornt_mtx4, &mtx4_trans);
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

t_ray	ray_for_pixel(t_camera *camera, int	px, int py)
{
	double	xoffset;
	double	yoffset;
	double	world_x;
	double	world_y;
	t_vcpnt	pixel;
	t_vcpnt	cm_pnt;
	t_vcpnt	std_pnt;
	t_vcpnt	origin;
	t_vcpnt	dir;
	t_ray	res;

	xoffset = (px + 0.5) * camera->pixel_size;
	yoffset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - xoffset;
	world_y = camera->half_height - yoffset;
	cm_pnt = (t_vcpnt){world_x, world_y, -1, 1};
	pixel = mult_mtx4_vcpnt4(&camera->inv_trans, &cm_pnt);
	std_pnt = (t_vcpnt){0,0,0,1};
	origin = mult_mtx4_vcpnt4(&camera->inv_trans, &std_pnt);
	dir = vec_subs(&pixel, &origin);
	dir = vec_norm(&dir);
	res = (t_ray){origin, dir};
	return (res);
}

void	setup_camera(t_camera *c, int hsize, int vsize, double fov)
{
	t_vcpnt	from;
	t_vcpnt	to;
	t_vcpnt	up;

	c->hsize = hsize;
	c->vsize = vsize;
	c->field_of_view = fov;
	from = (t_vcpnt){0, 0, -5, 1};
	to = (t_vcpnt){0, 0, 0, 1};
	up = (t_vcpnt){0, 1, 0, 0};
	c->transform = view_transform(&from, &to, &up);
	c->inv_trans = mtx4_inverse(&c->transform);
}
