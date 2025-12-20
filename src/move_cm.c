/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:52:50 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 02:12:15 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	rotate_camera(t_master *param, int key)
{
	double	rot_speed;

	rot_speed = 0.1;
	if (key == MLX_KEY_KP_2) // Look UP (Pitch +)
		key_rotate(&param->camera, 0, -rot_speed); // Negative usually looks up
	if (key == MLX_KEY_KP_8) // Look DOWN (Pitch -)
		key_rotate(&param->camera, 0, rot_speed);
	if (key == MLX_KEY_KP_4) // Look LEFT (Yaw -)
		key_rotate(&param->camera, -rot_speed, 0);
	if (key == MLX_KEY_KP_6) // Look RIGHT (Yaw +)
		key_rotate(&param->camera, rot_speed, 0);
}

t_mov_supp	pre_key_hook(t_master *param)
{
	t_mov_supp	mov_dir;

	mov_dir.wrld_up = (t_vcpnt){0, 1, 0, 0};
	mov_dir.mov_speed = 0.5;
	mov_dir.rot_speed = 0.1;
	mov_dir.forward = vec_subs(&param->camera.to, &param->camera.from);
	mov_dir.forward = vec_norm(&mov_dir.forward);
	mov_dir.right = vec_cross(&mov_dir.forward, &mov_dir.wrld_up);
	mov_dir.right = vec_norm(&mov_dir.right);
	return (mov_dir);
}

void	hook_sup_da(t_master *param, t_mov_supp *calc, int key)
{
	if (key == MLX_KEY_A)
	{
		calc->mv_vec = vec_scale(&calc->right, calc->mov_speed);
		param->camera.from = vec_add(&param->camera.from, &calc->mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc->mv_vec);
	}
	else if (key == MLX_KEY_D)
	{
		calc->mv_vec = vec_scale(&calc->right, -calc->mov_speed); // Note the minus!
		param->camera.from = vec_add(&param->camera.from, &calc->mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc->mv_vec);
	}
}

void	hook_sup_vertical(t_master *param, t_mov_supp *calc, int key)
{
	if (key == MLX_KEY_E)
	{
		calc->mv_vec = vec_scale(&calc->wrld_up, calc->mov_speed);
		param->camera.from = vec_add(&param->camera.from, &calc->mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc->mv_vec);
	}
	else if (key == MLX_KEY_Q) // Move DOWN (Elevation -)
	{
		calc->mv_vec = vec_scale(&calc->wrld_up, -calc->mov_speed);
		param->camera.from = vec_add(&param->camera.from, &calc->mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc->mv_vec);
	}
}

void mlx_hook_keys_supp(t_master *param, int key)
{
	t_mov_supp calc;

	calc = pre_key_hook(param);
	if (key == MLX_KEY_W) // Forward
	{
		calc.mv_vec = vec_scale(&calc.forward, calc.mov_speed);
		param->camera.from = vec_add(&param->camera.from, &calc.mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc.mv_vec);
	}
	else if (key == MLX_KEY_S) // Backward
	{
		calc.mv_vec = vec_scale(&calc.forward, -calc.mov_speed); // Note the minus!
		param->camera.from = vec_add(&param->camera.from, &calc.mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc.mv_vec);
	}
	else if (key == MLX_KEY_D || key == MLX_KEY_A)
		hook_sup_da(param, &calc, key);
	else if (key == MLX_KEY_E || key == MLX_KEY_Q)
		hook_sup_vertical(param, &calc, key);
	else
		rotate_camera(param, key);
}

void	mlx_hook_keys(mlx_key_data_t keydata, void *master)
{
	t_master	*param;

	param = (t_master *)master;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			mlx_close_window(param->mlx);
			return ;
		}
		else
			mlx_hook_keys_supp(param, keydata.key);
		setup_camera(&param->camera, param->camera.hsize,param->camera.vsize, param->camera.field_of_view);
		printf("Re-rendering...\n");
		render(param, &param->camera, param->img);
	}
}

t_mtx4 rotate_any_axis(t_vcpnt axis, double angle)
{
	t_mtx4	m;
	double	c = cos(angle);
	double	s = sin(angle);
	double	t = 1.0 - c;
	double	x = axis.vp[0], y = axis.vp[1], z = axis.vp[2];

	get_id_mtx4(&m); // Start with Identity

	m.mtx[0][0] = t*x*x + c;
	m.mtx[0][1] = t*x*y - s*z;
	m.mtx[0][2] = t*x*z + s*y;
	m.mtx[1][0] = t*x*y + s*z;
	m.mtx[1][1] = t*y*y + c;
	m.mtx[1][2] = t*y*z - s*x;
	m.mtx[2][0] = t*x*z - s*y;
	m.mtx[2][1] = t*y*z + s*x;
	m.mtx[2][2] = t*z*z + c;

	return (m);
}

void key_rotate(t_camera *cam, double yaw_speed, double pitch_speed)
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
