/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:49:30 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 05:25:04 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	parse_figures(t_master *app, char **tokens)
{
	if (ft_strncmp(tokens[0], "sp", 3) == 0)
	{
		if (!pr_sp(app, tokens))
			return (prnt_err("Spotted wrong input in Sphere"));
	}
	else if (ft_strncmp(tokens[0], "pl", 3) == 0)
	{
		if (!pr_pl(app, tokens))
			return (prnt_err("Spotted wrong input in Plane"));
	}
	else if (ft_strncmp(tokens[0], "cy", 3) == 0)
	{
		if (!pr_cl(app, tokens))
			return (prnt_err("Spotted wrong input in Cylinder"));
	}
	else
	{
		return (prnt_err("Unknown identifier in scene file"));
	}
	return (1);
}

int	parse_mobjects(t_master *app, char **tokens)
{
	if (ft_strncmp(tokens[0], "A", 2) == 0)
	{
		if (!pr_amb(app, tokens))
			return (prnt_err("Spotted wrong input in Ambient"));
		else
			return (1);
	}
	else if (ft_strncmp(tokens[0], "C", 2) == 0)
	{
		if (!pr_cm(app, tokens))
			return (prnt_err("Spotted wrong input in Camera"));
		else
			return (1);
	}
	else if (ft_strncmp(tokens[0], "L", 2) == 0)
	{
		if (!parse_light(app, tokens))
			return (prnt_err("Spotted wrong input in Light"));
		else
			return (1);
	}
	return (0);
}
