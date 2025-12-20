/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:49:05 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 05:25:43 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	check_if_open(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
		p_err("Could not open file", NULL, false);
}

int	parse_data(t_master *app, char *file)
{
	t_parse	pr_supp;

	if (!check_extension(file))
		p_err("Invalid file extension", NULL, false);
	check_if_open(file, &pr_supp.fd);
	app->o_fd = pr_supp.fd;
	while (1)
	{
		pr_supp.line = get_next_line(pr_supp.fd);
		pr_supp.len = ft_strlen(pr_supp.line);
		if (pr_supp.len > 0 && pr_supp.line[pr_supp.len - 1] == '\n')
			pr_supp.line[pr_supp.len - 1] = '\0';
		app->cur_line = pr_supp.line;
		if (!pr_supp.line)
			break ;
		if (pr_supp.line[0] != '\0')
			if (!parse_line(app, pr_supp.line))
				p_err("", app, 1);
		free(pr_supp.line);
		pr_supp.line = NULL;
	}
	close(pr_supp.fd);
	if (!check_main_obj(app))
		p_err("Missing mandatory objects", app, true);
	return (1);
}

int	parse_line(t_master *app, char *line)
{
	char	**tokens;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0])
		return (prnt_err("Malloc failed in parse_line"));
	printf("cur token is: %s\n", tokens[0]);
	if (!parse_mobjects(app, tokens))
	{
		if (!parse_figures(app, tokens))
			return (free_split(tokens), 0);
	}
	free_split(tokens);
	return (1);
}
