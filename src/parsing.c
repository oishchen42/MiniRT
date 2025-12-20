/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:05:08 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 03:42:57 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_extension(char *filename)
{
	char *dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || dot == filename)
		return (0);
	if (ft_strncmp(dot, ".rt", 4) != 0)
		return (0);
	return (1);
}

int	parse_figures(t_master *app, char **tokens)
{
	if (ft_strncmp(tokens[0], "sp", 3) == 0)
	{
		if (!pr_sp(app, tokens))
			p_err("Spotted wrong input in Sphere", app, false);
	}
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
	{
		if (!pr_pl(app, tokens))
			p_err("Spotted wrong input in Plane", app, false);
	}
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
	{
		if (!pr_cl(app, tokens))
			p_err("Spotted wrong input in Cylinder", app, false);
	}
	else
	{
		p_err("Unknown identifier in scene file", app, false);
	}
	return (1);
}

int	parse_mobjects(t_master *app, char **tokens)
{
	if (ft_strncmp(tokens[0], "A", 2) == 0)
	{
		if (!pr_amb(app, tokens))
			p_err("Spotted wrong input in Ambient", app, false);
		else
			return (1);
	}
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
	{
		if (!pr_cm(app, tokens))
			p_err("Spotted wrong input in Camera", app, false);
		else
			return (1);
	}
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
	{
		if (!parse_light(app, tokens))
			p_err("Spotted wrong input in Light", app, false);
		else
			return (1);
	}
	return (0);
}

int parse_line(t_master *app, char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (prnt_err("Malloc failed in parse_line"));
	printf("cur token is: %s\n", tokens[0]);
	app->split = tokens;
	if (!parse_mobjects(app, tokens))
	{
		if (!parse_figures(app, tokens))
			return (0);
	}
	free_split(tokens);
	return (1);
}

int	check_main_obj(t_master *app)
{
	if (app->counts.amb_count != 1)
	{
		printf("ambinet n: %d\n", app->counts.amb_count);
		return (prnt_err("Error: Scene must have exactly one Ambient Light (A)"));
	}
	if (app->counts.cam_count != 1)
		return (prnt_err("Error: Scene must have exactly one Camera (C)"));
	if (app->counts.light_count != 1)
		return (prnt_err("Error: Scene must have exactly one Light (L)"));

	return (1);
}

int	parse_data(t_master *app, char *file)
{
	int		fd;
	char	*line;
	size_t	len;

	if (!check_extension(file))
		p_err("Invalid file extension", NULL, false);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		p_err("Could not open file", NULL, false);
	app->counts = (t_counters){0, 0, 0};
	app->o_fd = fd;
	while (1)
	{
		line = get_next_line(fd);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		app->cur_line = line;
		if (!line)
			break;
		if (line[0] != '\0') 
			if (!parse_line(app, line))
				break;
		free(line);
		line = NULL;
	}
	close(fd);
	if (!check_main_obj(app))
		p_err("Missing mandatory objects", app, true);
	printf("all good\n");
	return (1);
}

int	pr_amb(t_master *app, char **tokens)
{
	if (app->counts.amb_count > 0)
		return (prnt_err("Duplicate Ambient Light defined"));
	app->counts.amb_count++;
	printf("here in ambinet\n");
	if (!tokens[1] || !tokens[2] || tokens[3])
		return (prnt_err("Invalid Ambient Light arguments"));
	if (!valid_str(tokens[1]))
		return (0);
	app->amb.ratio = ft_atod(tokens[1]);
	if (app->amb.ratio < 0.0 || app->amb.ratio > 1.0)
		return (prnt_err("Ambient ratio must be between 0.0 and 1.0"));
	if (!get_vector(tokens[2], &app->amb.color, 0.0))
		return (0);
	from_high_2_low(&app->amb.color);
	return (1);
}

int	parse_2camera(t_master *app, char **tokens, t_cm_pr *pr_cm)
{
	if (!get_vector(tokens[1], &app->camera.from, 0.0))
		return (prnt_err("Invalid Camera Position"));
	app->camera.from.vp[3] = 1.0;
	if (!get_vector(tokens[2], &pr_cm->dir_vec, 0.0))
		return (prnt_err("Invalid Camera Orientation"));
	if (fabs(pr_cm->dir_vec.vp[0]) < EPSILON && fabs(pr_cm->dir_vec.vp[2]) < EPSILON)
		pr_cm->dir_vec.vp[0] += 0.1;
	pr_cm->dir_vec.vp[3] = 0.0;
	pr_cm->dir_vec = vec_norm(&pr_cm->dir_vec);
	app->camera.to = vec_add(&app->camera.from, &pr_cm->dir_vec);
	app->camera.to.vp[3] = 1.0;
	app->camera.hsize = 500.0;
	app->camera.vsize = 300.0;
	return (1);
}

int pr_cm(t_master *app, char **tokens)
{
	t_cm_pr	pr_cm;

	if (app->counts.cam_count > 0)
		return (prnt_err("Duplicate Camera defined"));
	app->counts.cam_count++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return(prnt_err("Invalid Camera arguments"));
	if (!parse_2camera(app, tokens, &pr_cm))
		return (0);
	if (fabs(pr_cm.dir_vec.vp[0]) < EPSILON && fabs(pr_cm.dir_vec.vp[2]) < EPSILON)
		app->camera.up = (t_vcpnt){0, 0, 1, 0};
	else
		app->camera.up = (t_vcpnt){0, 1, 0, 0};
	pr_cm.fov_deg = ft_atod(tokens[3]);
	//printf("fov: %f\n", pr_cm.fov_deg);
	if (pr_cm.fov_deg < 0.0 || pr_cm.fov_deg > 180.0)
		return (prnt_err("FOV must be between 0 and 180"));
	app->camera.field_of_view = pr_cm.fov_deg * (PI / 180.0);
	setup_camera(&app->camera, app->camera.hsize, app->camera.vsize, app->camera.field_of_view);
	return (1);
}

int	parse_light(t_master *app, char **tokens)
{
	t_lgt_pr	n_light;

	if (app->counts.light_count > 0)
		return (prnt_err("Duplicate Light defined"));
	app->counts.light_count++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (prnt_err("Invalid Light arguments"));
	if (!get_vector(tokens[1], &n_light.pos, 1.0))
		return (prnt_err("Invalid Light arguments"));
	if (!valid_str(tokens[2]))
		return (prnt_err("Unvalid light ratio"));
	n_light.ratio = ft_atod(tokens[2]);
	if (n_light.ratio < 0.0 || n_light.ratio > 1.0)
		return (prnt_err("Light brightness ratio must be between 0.0 and 1.0"));
	if (!get_vector(tokens[3], &n_light.color, 0.0))
		return (prnt_err("Invalid Light Color format"));
	from_high_2_low(&n_light.color);
	print_vpnt4(&n_light.color);
	n_light.new_light = create_light(&n_light.pos, &n_light.color, n_light.ratio);
	if (!n_light.new_light)
		return (prnt_err("Malloc err"));
	wadd_obj(&app->world, n_light.new_light, NULL);
	return (1);
}

int		pr_sp(t_master *app, char **tokens)
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

int check_normalized(t_vcpnt *vec)
{
	if (vec->vp[0] < -1.0 || vec->vp[0] > 1.0)
		return (0);
	if (vec->vp[1] < -1.0 || vec->vp[1] > 1.0)
		return (0);
	if (vec->vp[2] < -1.0 || vec->vp[2] > 1.0)
		return (0);
	if (fabs(vec->vp[0]) < EPSILON &&
		fabs(vec->vp[1]) < EPSILON &&
		fabs(vec->vp[2]) < EPSILON)
		return (0);
	return (1);
}

int		pr_pl(t_master *app, char **tokens)
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
	pl_pr.norm = vec_norm(&pl_pr.norm);
	pl_pr.trans_mtx = trans4(&pl_pr.orig);
	pl_pr.rot_mtx = get_rotation_matrix(&pl_pr.norm);
	pl_pr.res = mtxs_mult4(&pl_pr.trans_mtx, &pl_pr.rot_mtx);
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

int pr_cl(t_master *app, char **tokens)
{
	t_cl_pr	cl_pr;

	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4] ||
		!tokens[5] || tokens[6])
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
