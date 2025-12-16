/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:30:49 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/16 21:18:29 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <minirt.h>
#include <string.h>
#include <MLX42.h>

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

//int	main(int ac, char **av)
//{
//	(void)ac;
//	char *str;

//	if (ac < 2)
//		return (1);
//	str = av[1];
//	// int fd = open("scenes/test.rt", O_RDONLY);
//	// printf("%d\n", fd);
//	// return (0);
//	is_rt(str);
//	get_value(str);
//}