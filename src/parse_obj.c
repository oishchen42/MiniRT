/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:49:33 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 06:37:44 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	pr_amb(t_master *app, char **tokens)
{
	if (app->counts.amb_count > 0)
		return (prnt_err("Duplicate Ambient Light defined"));
	app->counts.amb_count++;
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
	if (fabs(pr_cm->dir_vec.vp[0]) < EPSILON
		&& fabs(pr_cm->dir_vec.vp[2]) < EPSILON)
		pr_cm->dir_vec.vp[0] += 0.1;
	pr_cm->dir_vec.vp[3] = 0.0;
	pr_cm->dir_vec = vec_norm(&pr_cm->dir_vec);
	app->camera.to = vec_add(&app->camera.from, &pr_cm->dir_vec);
	app->camera.to.vp[3] = 1.0;
	app->camera.hsize = 500.0;
	app->camera.vsize = 300.0;
	return (1);
}

int	pr_cm(t_master *app, char **tokens)
{
	t_cm_pr	pr_cm;

	if (app->counts.cam_count > 0)
		return (prnt_err("Duplicate Camera defined"));
	app->counts.cam_count++;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		return (prnt_err("Invalid Camera arguments"));
	if (!parse_2camera(app, tokens, &pr_cm))
		return (0);
	if (fabs(pr_cm.dir_vec.vp[0]) < EPSILON
		&& fabs(pr_cm.dir_vec.vp[2]) < EPSILON)
		app->camera.up = (t_vcpnt){0, 0, 1, 0};
	else
		app->camera.up = (t_vcpnt){0, 1, 0, 0};
	pr_cm.fov_deg = ft_atod(tokens[3]);
	if (pr_cm.fov_deg < 0.0 || pr_cm.fov_deg > 180.0)
		return (prnt_err("FOV must be between 0 and 180"));
	app->camera.field_of_view = pr_cm.fov_deg * (PI / 180.0);
	setup_camera(&app->camera, app->camera.hsize,
		app->camera.vsize, app->camera.field_of_view);
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
	n_light.new_light = create_light(&n_light.pos, &n_light.color,
			n_light.ratio);
	if (!n_light.new_light)
		return (prnt_err("Malloc err"));
	wadd_obj(&app->world, n_light.new_light, NULL);
	return (1);
}
