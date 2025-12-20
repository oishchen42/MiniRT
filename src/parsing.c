/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:05:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 06:41:22 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_extension(char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	if (ft_strncmp(dot, ".rt", 4) != 0)
		return (0);
	return (1);
}

int	check_main_obj(t_master *app)
{
	if (app->counts.amb_count != 1)
	{
		return (
			prnt_err("Error: Scene must have exactly one Ambient Light (A)"));
	}
	if (app->counts.cam_count != 1)
		return (prnt_err("Error: Scene must have exactly one Camera (C)"));
	if (app->counts.light_count != 1)
		return (prnt_err("Error: Scene must have exactly one Light (L)"));
	return (1);
}

int	check_normalized(t_vcpnt *vec)
{
	if (vec->vp[0] < -1.0 || vec->vp[0] > 1.0)
		return (0);
	if (vec->vp[1] < -1.0 || vec->vp[1] > 1.0)
		return (0);
	if (vec->vp[2] < -1.0 || vec->vp[2] > 1.0)
		return (0);
	if (fabs(vec->vp[0]) < EPSILON
		&& fabs(vec->vp[1]) < EPSILON
		&& fabs(vec->vp[2]) < EPSILON)
		return (0);
	return (1);
}
