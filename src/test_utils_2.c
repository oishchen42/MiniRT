/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:17:37 by tdietz-r          #+#    #+#             */
/*   Updated: 2025/12/20 06:36:20 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	create_mtx3_stb(t_mtx3 *mtx)
{
	mtx->mtx[0][0] = 1;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 6;
	mtx->mtx[1][0] = -5;
	mtx->mtx[1][1] = 8;
	mtx->mtx[1][2] = -4;
	mtx->mtx[2][0] = 2;
	mtx->mtx[2][1] = 6;
	mtx->mtx[2][2] = 4;
}

void	print_mtx3(t_mtx3 *mtx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SIZE_MTX3)
	{
		j = -1;
		while (++j < SIZE_MTX3)
			printf("[%.1f]", mtx->mtx[i][j]);
		printf("\n");
	}
}

void	create_mtx2_stb(t_mtx2 *mtx)
{
	mtx->mtx[0][0] = 1;
	mtx->mtx[0][1] = 5;
	mtx->mtx[1][0] = -3;
	mtx->mtx[1][1] = 2;
}

void	print_mtx2(t_mtx2 *mtx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SIZE_MTX2)
	{
		j = -1;
		while (++j < SIZE_MTX2)
			printf("[%.1f]", mtx->mtx[i][j]);
		printf("\n");
	}
}

//void	print_vpnt4(t_vcpnt *ent)
//{
//	printf("{%f, %f, %f, %f}\n", ent->vp[0], ent->vp[1], ent->vp[2], ent->vp[3]);
//}
