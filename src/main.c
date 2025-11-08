/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:30:49 by oishchen          #+#    #+#             */
/*   Updated: 2025/10/27 16:55:21 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <MLX42.h>

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	main()
{
	int	image_width = 512;
	int	image_heights = 512;
	mlx_t	*cpy_mlx;
	mlx_image_t	*image;

	cpy_mlx = mlx_init(image_width, image_heights, "FIrst try", 1);
	image = mlx_new_image(cpy_mlx, 512, 512);
	for (int i = 0; i < image_heights; i++)
	{
		for (int j = 0; j < image_width; j++)
		{
			float r = (float)i / (image_heights - 1);
			float g = (float)j / (image_width - 1);
			float b = 0.0;
			float a = 1.0;
			int	ir = (int)(255.999 * r);
			int	ig = (int)(255.999 * g);
			int	ib = (int)(255.999 * b);
			int	ia = (int)(255.999 * a);
			uint32_t color = ft_pixel(ir, ig, ib, ia);
			mlx_put_pixel(image, i, j, color);
		}
	}
	mlx_image_to_window(cpy_mlx, image, 0, 0);
	mlx_loop(cpy_mlx);
	mlx_close_window(cpy_mlx);
	mlx_terminate(cpy_mlx);
}