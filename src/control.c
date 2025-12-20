/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:52:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 06:00:35 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	render_hook(void *param)
{
	t_master	*app;
	t_ray		ray;
	t_vcpnt		color;
	int			i;
	int			j;

	app = (t_master *)param;
	j = -1;
	while (++j < app->camera.vsize)
	{
		i = -1;
		while (++i < app->camera.hsize)
		{
			ray = ray_for_pixel(&app->camera, i, j);
			color = world_inter(app, &ray);
			mlx_put_pixel(app->img, i, j, vcpnt_2_rgba(&color));
		}
	}
}

void	controls_hook(void *param)
{
	t_master	*app;

	app = (t_master *)param;
	if (mlx_is_key_down(app->mlx, MLX_KEY_W))
	{
		app->camera.transform.mtx[2][3] += 0.5;
		app->camera.inv_trans = mtx4_inverse(&app->camera.transform);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_S))
	{
		app->camera.transform.mtx[2][3] -= 0.5;
		app->camera.inv_trans = mtx4_inverse(&app->camera.transform);
	}
	if (mlx_is_key_down(app->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(app->mlx);
}
