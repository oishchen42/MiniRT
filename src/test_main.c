/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:21:32 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/20 21:57:48 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main()
{
	t_mtx4	mtx1;
	t_mtx4	mtx2;
	t_mtx4	mtx3;
	t_mtx4	mtx3_cp;

	create_mtx_stb(&mtx1);
	create_mtx_stb2(&mtx2);

	print_mtx(&mtx1);
	printf("\n");
	print_mtx(&mtx2);
	mtx3 = mtxs_mult(&mtx1, &mtx2);
	printf("\n");
	print_mtx(&mtx3);
	printf("\n");
	mtx3_cp = id_mtx(&mtx3);
	print_mtx(&mtx3_cp);
	return (0);
}