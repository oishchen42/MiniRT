/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:54:54 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/18 20:14:38 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	render(t_master *app, t_camera *cm, mlx_image_t *img)
{
	int		y;
	int		x;
	t_ray	ray;
	t_vcpnt	color;

	y = -1;
	while (++y < cm->vsize)
	{
		x = -1;
		while (++x < cm->hsize)
		{
			ray = ray_for_pixel(cm, x, y);
			color = world_inter(app, &ray);
			mlx_put_pixel(img, x, y, vcpnt_2_rgba(&color));
		}
	}
}
