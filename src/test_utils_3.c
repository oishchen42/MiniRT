/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:18:07 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 16:19:10 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	clean_lst(void *content)
{
	free(content);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	to_byte(double val)
{
	if (val < 0)
		val = 0;
	if (val > 1)
		val = 1;
	return ((int)(val * 255));
}

int	vcpnt_2_rgba(t_vcpnt *color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	a = 255;
	r = to_byte(color->vp[0]);
	g = to_byte(color->vp[1]);
	b = to_byte(color->vp[2]);
	return (r << 24 | g << 16 | b << 8 | a);
}
