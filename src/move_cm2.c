/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cm2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 05:39:58 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 05:46:03 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mtx4	rotate_any_axis(t_vcpnt axis, double angle)
{
	t_mtx4	m;
	double	c;
	double	s;
	double	t;
	t_xyz	xyz;

	c = cos(angle);
	s = sin(angle);
	get_id_mtx4(&m);
	t = 1.0 - c;
	xyz.x = axis.vp[0];
	xyz.y = axis.vp[1];
	xyz.z = axis.vp[2];
	m.mtx[0][0] = t * xyz.x * xyz.x + c;
	m.mtx[0][1] = t * xyz.x * xyz.y - s * xyz.z;
	m.mtx[0][2] = t * xyz.x * xyz.z + s * xyz.y;
	m.mtx[1][0] = t * xyz.x * xyz.y + s * xyz.z;
	m.mtx[1][1] = t * xyz.y * xyz.y + c;
	m.mtx[1][2] = t * xyz.y * xyz.z - s * xyz.x;
	m.mtx[2][0] = t * xyz.x * xyz.z - s * xyz.y;
	m.mtx[2][1] = t * xyz.y * xyz.z + s * xyz.x;
	m.mtx[2][2] = t * xyz.z * xyz.z + c;
	return (m);
}

void	key_rotate(t_camera *cam, double yaw_speed, double pitch_speed)
{
	t_rotate	rt;

	rt.world_up = (t_vcpnt){0, 1, 0, 0};
	rt.direction = vec_subs(&cam->to, &cam->from);
	rt.direction = vec_norm(&rt.direction);
	if (fabs(yaw_speed) > EPSILON)
	{
		rt.rot_mtx = rotate_any_axis(rt.world_up, yaw_speed);
		rt.direction = mult_mtx4_vcpnt4(&rt.rot_mtx, &rt.direction);
	}
	if (fabs(pitch_speed) > EPSILON)
	{
		rt.right = vec_cross(&rt.direction, &rt.world_up);
		rt.right = vec_norm(&rt.right);
		rt.rot_mtx = rotate_any_axis(rt.right, pitch_speed);
		rt.temp_dir = mult_mtx4_vcpnt4(&rt.rot_mtx, &rt.direction);
		rt.dot = vec_dot(&rt.temp_dir, &rt.world_up);
		if (rt.dot < 0.99 && rt.dot > -0.99)
			rt.direction = rt.temp_dir;
	}
	rt.direction = vec_norm(&rt.direction);
	cam->to = vec_add(&cam->from, &rt.direction);
}

void	rotate_camera(t_master *param, int key)
{
	double	rot_speed;

	rot_speed = 0.1;
	if (key == MLX_KEY_KP_2)
		key_rotate(&param->camera, 0, -rot_speed);
	if (key == MLX_KEY_KP_8)
		key_rotate(&param->camera, 0, rot_speed);
	if (key == MLX_KEY_KP_4)
		key_rotate(&param->camera, -rot_speed, 0);
	if (key == MLX_KEY_KP_6)
		key_rotate(&param->camera, rot_speed, 0);
}
