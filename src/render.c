/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 20:54:54 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/11 21:43:57 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	render(t_world *w, t_camera *cm, mlx_image_t *img)
{
	int	y;
	int	x;

	y = -1;
	while (++y < cm->vsize)
	{
		x = -1;
		while (++x < cm->hsize)
		{
			t_ray ray = ray_for_pixel(cm, x, y);
			t_vcpnt color = world_inter(w, &ray);
			mlx_put_pixel(img, x, y, vcpnt_2_rgba(&color));
		}
	}
}