/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:26:11 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/22 16:08:49 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <math.h>
#include <time.h>

void	create_mtx4_rnd(t_mtx4 *mtx)
{
	int	i;
	int	j;

	srand(time(NULL));
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			mtx->mtx[i][j] = rand() % 100;
			//printf("[%.1f]", mtx->mtx[i][j]);
		}
		printf("\n");
	}
}

void	create_mtx4_stb(t_mtx4 *mtx)
{
	mtx->mtx[0][0] = -5;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 6;
	mtx->mtx[0][3] = -8;
	mtx->mtx[1][0] = 1;
	mtx->mtx[1][1] = -5;
	mtx->mtx[1][2] = 1;
	mtx->mtx[1][3] = 8;
	mtx->mtx[2][0] = 7;
	mtx->mtx[2][1] = 7;
	mtx->mtx[2][2] = -6;
	mtx->mtx[2][3] = -7;
	mtx->mtx[3][0] = 1;
	mtx->mtx[3][1] = -3;
	mtx->mtx[3][2] = 7;
	mtx->mtx[3][3] = 4;
}

void	create_mtx4_stb2(t_mtx4 *mtx)
{
	mtx->mtx[0][0] = -2;
	mtx->mtx[0][1] = -8;
	mtx->mtx[0][2] = 3;
	mtx->mtx[0][3] = 5;
	mtx->mtx[1][0] = -3;
	mtx->mtx[1][1] = 1;
	mtx->mtx[1][2] = 7;
	mtx->mtx[1][3] = 3;
	mtx->mtx[2][0] = 1;
	mtx->mtx[2][1] = 2;
	mtx->mtx[2][2] = -9;
	mtx->mtx[2][3] = 6;
	mtx->mtx[3][0] = -6;
	mtx->mtx[3][1] = 7;
	mtx->mtx[3][2] = 7;
	mtx->mtx[3][3] = -9;
}

void	print_mtx4(t_mtx4 *mtx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		j = -1;
		while (++j < SIZE_MTX4)
			printf("[%.1f]", mtx->mtx[i][j]);
		printf("\n");
	}
}

void	print_inv4(t_mtx4 *mtx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SIZE_MTX4)
	{
		j = -1;
		while (++j < SIZE_MTX4)
			printf("[%.5f]", mtx->mtx[i][j]);
		printf("\n");
	}
}

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
