/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:49:35 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 05:20:53 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	record_pl(t_pl_pr *pl_pr)
{
	pl_pr->norm = vec_norm(&pl_pr->norm);
	pl_pr->trans_mtx = trans4(&pl_pr->orig);
	pl_pr->rot_mtx = get_rotation_matrix(&pl_pr->norm);
	pl_pr->res = mtxs_mult4(&pl_pr->trans_mtx, &pl_pr->rot_mtx);
}

int	pr_pl(t_master *app, char **tokens)
{
	t_pl_pr	pl_pr;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (prnt_err("Invalid Plane arguments"));
	if (!get_vector(tokens[3], &pl_pr.mat_clr, 0.0))
	{
		printf("token[3] in plane: |%s|\n", tokens[3]);
		return (prnt_err("Invalid Plane Color"));
	}
	from_high_2_low(&pl_pr.mat_clr);
	pl_pr.obj = plane(&pl_pr.mat_clr);
	if (!pl_pr.obj)
		return (prnt_err("Malloc failed"));
	wadd_obj(&app->world, NULL, pl_pr.obj);
	if (!get_vector(tokens[1], &pl_pr.orig, 1.0))
		return (prnt_err("Invalid Plane Position"));
	if (!get_vector(tokens[2], &pl_pr.norm, 0.0))
		return (prnt_err("Invalid Plane Normal"));
	if (!check_normalized(&pl_pr.norm))
		return (prnt_err("Invalid Plane Normal values"));
	record_pl(&pl_pr);
	create_transform_mtx4(pl_pr.obj, &pl_pr.res);
	return (1);
}

void	record_cl_values(t_cl_pr cl_pr)
{
	cl_pr.obj->data.cl.radi = cl_pr.dia / 2.0;
	cl_pr.obj->data.cl.min = -cl_pr.height / 2.0;
	cl_pr.obj->data.cl.max = cl_pr.height / 2.0;
	cl_pr.trans_mtx = trans4(&cl_pr.obj->data.cl.orig);
	cl_pr.rot_mtx = get_rotation_matrix(&cl_pr.norm);
	cl_pr.scale_vec = (t_vcpnt){cl_pr.obj->data.cl.radi,
		1.0, cl_pr.obj->data.cl.radi, 0};
	cl_pr.scale_mtx = scale4(&cl_pr.scale_vec);
	cl_pr.temp = mtxs_mult4(&cl_pr.rot_mtx, &cl_pr.scale_mtx);
	cl_pr.res = mtxs_mult4(&cl_pr.trans_mtx, &cl_pr.temp);
	create_transform_mtx4(cl_pr.obj, &cl_pr.res);
	from_high_2_low(&cl_pr.obj->data.cl.mat.color);
}

int	pr_cl(t_master *app, char **tokens)
{
	t_cl_pr	cl_pr;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4]
		|| !tokens[5] || tokens[6])
		return (prnt_err("Invalid Cylinder arguments"));
	if (!get_vector(tokens[5], &cl_pr.mat_clr, 0.0))
		return (prnt_err("Invalid Cylinder Color"));
	cl_pr.obj = cylinder(&cl_pr.mat_clr, NULL, -1.0, 1.0);
	if (!cl_pr.obj)
		return (prnt_err("Malloc failed"));
	wadd_obj(&app->world, NULL, cl_pr.obj);
	if (!get_vector(tokens[1], &cl_pr.obj->data.cl.orig, 1.0))
		return (prnt_err("Invalid Cylinder Position"));
	if (!get_vector(tokens[2], &cl_pr.norm, 0.0))
		return (prnt_err("Invalid Cylinder Normal"));
	if (!check_normalized(&cl_pr.norm))
		return (prnt_err("Invalid Cylinder Normal values"));
	cl_pr.norm = vec_norm(&cl_pr.norm);
	if (!valid_str(tokens[3]) || !valid_str(tokens[4]))
		return (prnt_err("Invalid Cylinder dimensions"));
	cl_pr.dia = ft_atod(tokens[3]);
	cl_pr.height = ft_atod(tokens[4]);
	if (cl_pr.dia < 0.0 || cl_pr.height < 0.0)
		return (prnt_err("Cylinder dimensions cannot be negative"));
	return (record_cl_values(cl_pr), 1);
}

int	pr_sp(t_master *app, char **tokens)
{
	t_sp_pr	sp_pr;

	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (prnt_err("Invalid Sphere arguments"));
	if (!get_vector(tokens[3], &sp_pr.mat_clr, 0.0))
		return (prnt_err("Invalid Sphere Color"));
	from_high_2_low(&sp_pr.mat_clr);
	sp_pr.obj = sphere(&sp_pr.mat_clr);
	if (!sp_pr.obj)
		return (prnt_err("Malloc failed"));
	wadd_obj(&app->world, NULL, sp_pr.obj);
	if (!get_vector(tokens[1], &sp_pr.sp.orig, 1.0))
		return (prnt_err("Invalid Sphere Position"));
	if (!valid_str(tokens[2]))
		return (prnt_err("Invalid Sphere Diameter"));
	sp_pr.dia = ft_atod(tokens[2]);
	if (sp_pr.dia < 0.0)
		return (prnt_err("Sphere diameter cannot be negative"));
	sp_pr.radi = sp_pr.dia / 2.0;
	sp_pr.trans_mtx = trans4(&sp_pr.sp.orig);
	sp_pr.scale_vec = (t_vcpnt){sp_pr.radi, sp_pr.radi, sp_pr.radi, 0};
	sp_pr.scale_mtx = scale4(&sp_pr.scale_vec);
	sp_pr.res = mtxs_mult4(&sp_pr.trans_mtx, &sp_pr.scale_mtx);
	create_transform_mtx4(sp_pr.obj, &sp_pr.res);
	return (1);
}
