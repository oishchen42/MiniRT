/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:51:43 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/16 20:25:16 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	free_double(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		free(split[i]);
	}
	free(split);
}

void	pirnt_split_content(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		printf("%s\n", split[i]);
	}
}

static void	add_default_spheres(t_world *wrld)
{
	t_obj		*sp1;
	t_obj		*sp2;
	t_material	mat;
	t_mtx4		scl;
	t_vcpnt		v_scl;

	mat.color = (t_vcpnt){0.8, 1.0, 0.6, 1};
	mat.diffuse = 0.7;
	mat.specular = 0.2;
	mat.shiness = 200;
	mat.ambient = 0.5;
	sp1 = sphere(&mat, NULL);
	wadd_obj(wrld, NULL, sp1);
	v_scl = (t_vcpnt){0.5, 0.5, 0.5, 1};
	scl = scale4(&v_scl);
	sp2 = sphere(NULL, NULL);
	create_transform_mtx4(sp2, &scl);
	wadd_obj(wrld, NULL, sp2);
}

//Timo updated function. To many declarations. Split with help function
void	default_world(t_world *wrld)
{
	t_light	*light;
	t_vcpnt	l_pnt;
	t_vcpnt	l_int;

	*wrld = init_world();
	l_pnt = (t_vcpnt){-10, 10, -10, 1};
	l_int = (t_vcpnt){1, 1, 1, 1};
	light = create_light(&l_pnt, &l_int);
	wadd_obj(wrld, light, NULL);
	add_default_spheres(wrld);
}
