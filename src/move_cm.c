/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:52:50 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 05:49:50 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

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
		calc->mv_vec = vec_scale(&calc->right, -calc->mov_speed);
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
	else if (key == MLX_KEY_Q)
	{
		calc->mv_vec = vec_scale(&calc->wrld_up, -calc->mov_speed);
		param->camera.from = vec_add(&param->camera.from, &calc->mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc->mv_vec);
	}
}

void	mlx_hook_keys_supp(t_master *param, int key)
{
	t_mov_supp	calc;

	calc = pre_key_hook(param);
	if (key == MLX_KEY_W)
	{
		calc.mv_vec = vec_scale(&calc.forward, calc.mov_speed);
		param->camera.from = vec_add(&param->camera.from, &calc.mv_vec);
		param->camera.to = vec_add(&param->camera.to, &calc.mv_vec);
	}
	else if (key == MLX_KEY_S)
	{
		calc.mv_vec = vec_scale(&calc.forward, -calc.mov_speed);
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
		setup_camera(&param->camera, param->camera.hsize,
			param->camera.vsize, param->camera.field_of_view);
		printf("Re-rendering...\n");
		render(param, &param->camera, param->img);
	}
}
