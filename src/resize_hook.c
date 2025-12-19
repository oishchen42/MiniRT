/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:55:03 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/19 01:24:27 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_master *app;

	app = (t_master *)param;
	if (width == 0 || height == 0)
		return;
	mlx_resize_image(app->img, width, height);
	app->camera.hsize = (double)width;
	app->camera.vsize = (double)height;
	setup_camera(&app->camera, app->camera.hsize, app->camera.vsize, app->camera.field_of_view);
	render(app, &app->camera, app->img);
}