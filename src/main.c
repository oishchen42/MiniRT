/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:30:49 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 02:39:10 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#define STD_ARGUM "Not enough arguments, try: ./minirt scene"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	p_err(char *msg, t_master *app, bool is_exit_nrm)
{
	write(STDERR_FILENO, "Error: ", 7);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (app)
	{
		printf("no segfault before the wclear world\n");
		wclear_world(&app->world);
		printf("no segfault after the wclear world\n");
		if (app->split)
		{
			//free_split(app->split);
			printf("no sef fault after the free_split\n");
		}
		if (app->cur_line)
		{
			free(app->cur_line);
			printf("no seg fault after the free line\n");
		}
		close(app->o_fd);
	}
	if (is_exit_nrm)
		exit(0);
	else
		exit(1);
	return (0);
}

int	prnt_err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	return (0);
}

t_master	init_master()
{
	t_master	mstr;

	mstr.world = init_world();
	mstr.split = NULL;
	mstr.cur_line = NULL;
	mstr.amb.is_amb = 0;
	mstr.o_fd = -1;
	return (mstr);
}

int	init_mlx_hooks(t_master *app)
{
	if (!(app->mlx = mlx_init((int)app->camera.hsize,
	(int)app->camera.vsize, "MLX42", true)))
		return (prnt_err("mlx_init is broken"));
	if (!(app->img = mlx_new_image(app->mlx, (int)app->camera.hsize,
		(int)app->camera.vsize)))
		return (prnt_err("mlx_new_image is broken"));
	if (mlx_image_to_window(app->mlx, app->img, 0, 0) == -1)
		return (prnt_err("mlx_image_to_window is broken"));
	mlx_key_hook(app->mlx, &mlx_hook_keys, app);
	mlx_resize_hook(app->mlx, &resize_hook, app);
	return (1);
}

char	*get_filename(char *str)
{
	char	*res;

	res = ft_strrchr(str, '/');
	if (!res)
		return (str);
	return (res + 1);
}

void	print_obj_color(t_world *wrld)
{
	t_list	*cp_obj;
	t_obj	*obj;

	cp_obj = wrld->objs;
	while (cp_obj)
	{
		obj = cp_obj->content;
		printf("cur obj: ");
		if (obj->type == SPHERE)
		{
			printf("S\n");
			printf("color is: ");
			print_vpnt4(&obj->data.sp.mat.color);
		}
		if (obj->type == PLANE)
		{
			printf("PL\n");
			printf("color is: ");
			print_vpnt4(&obj->data.pl.mat.color);
		}
		if (obj->type == CYLINDER)
		{
			printf("CL\n");
			printf("color is: ");
			print_vpnt4(&obj->data.cl.mat.color);
		}
		cp_obj = cp_obj->next;
	}
}

int	main(int ac, char **av)
{
	char		*str;
	t_master	app;

	app = init_master();
	if (ac != 2)
		return (prnt_err((STD_ARGUM)), 1);
	str = av[1];
	//str = get_filename(str);
	//printf("my file name is: %s\n", str);
	if (!parse_data(&app, str))
		return (1);
	printf("no segfault\n");
	if (!init_mlx_hooks(&app))
		return (prnt_err("MLX init failed"));
	printf("no segfault\n");
	print_obj_color(&app.world);
	render(&app, &app.camera, app.img);
	mlx_loop(app.mlx);
	mlx_close_window(app.mlx);
	mlx_terminate(app.mlx);
	wclear_world(&app.world);
	return (0);
}

// Dispatcher: Identifies the line type
