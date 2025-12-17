/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:48:12 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 20:20:37 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

static t_vcpnt	get_sensor_point(t_camera *cam, int px, int py)
{
	double	world_x;
	double	world_y;

	world_x = cam->half_width - ((px + 0.5) * cam->pixel_size);
	world_y = cam->half_height - ((py + 0.5) * cam->pixel_size);
	return ((t_vcpnt){world_x, world_y, -1, 1});
}

//Timo updated function. To many declarations. Split with help function
t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	t_vcpnt	pixel;
	t_vcpnt	origin;
	t_vcpnt	dir;
	t_vcpnt	sensor;

	sensor = get_sensor_point(camera, px, py);
	pixel = mult_mtx4_vcpnt4(&camera->inv_trans, &sensor);
	origin = mult_mtx4_vcpnt4(&camera->inv_trans, &(t_vcpnt){0, 0, 0, 1});
	dir = vec_subs(&pixel, &origin);
	dir = vec_norm(&dir);
	return ((t_ray){origin, dir});
}

void	setup_camera(t_camera *c, double hsize, double vsize, double fov)
{
	c->hsize = hsize; // horiz size
	c->vsize = vsize; // vertec size
	c->field_of_view = fov;
	camera(c);
	//from = (t_vcpnt){0, 0, -5, 1};
	//to = (t_vcpnt){0, 0, 0, 1};
	//up = (t_vcpnt){0, 1, 0, 1};
	c->transform = view_transform(&c->from, &c->to, &c->up);
	c->inv_trans = mtx4_inverse(&c->transform);
}

void	resize_cm(t_camera *cm, t_vcpnt	*new_from)
{
	cm->from = *new_from;
	cm->transform = view_transform(&cm->from, &cm->to, &cm->up);
	cm->inv_trans = mtx4_inverse(&cm->transform);
}
