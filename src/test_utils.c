/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:26:11 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/20 20:33:29 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <time.h>

void	create_mtx_rnd(t_mtx4 *mtx)
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

void	create_mtx_stb(t_mtx4 *mtx)
{
	mtx->mtx[0][0] = 1;
	mtx->mtx[0][1] = 2;
	mtx->mtx[0][2] = 3;
	mtx->mtx[0][3] = 4;
	mtx->mtx[1][0] = 5;
	mtx->mtx[1][1] = 6;
	mtx->mtx[1][2] = 7;
	mtx->mtx[1][3] = 8;
	mtx->mtx[2][0] = 9;
	mtx->mtx[2][1] = 8;
	mtx->mtx[2][2] = 7;
	mtx->mtx[2][3] = 6;
	mtx->mtx[3][0] = 5;
	mtx->mtx[3][1] = 4;
	mtx->mtx[3][2] = 3;
	mtx->mtx[3][3] = 2;
}

void	create_mtx_stb2(t_mtx4 *mtx)
{
	mtx->mtx[0][0] = -2;
	mtx->mtx[0][1] = 1;
	mtx->mtx[0][2] = 2;
	mtx->mtx[0][3] = 3;
	mtx->mtx[1][0] = 3;
	mtx->mtx[1][1] = 2;
	mtx->mtx[1][2] = 1;
	mtx->mtx[1][3] = -1;
	mtx->mtx[2][0] = 4;
	mtx->mtx[2][1] = 3;
	mtx->mtx[2][2] = 6;
	mtx->mtx[2][3] = 5;
	mtx->mtx[3][0] = 1;
	mtx->mtx[3][1] = 2;
	mtx->mtx[3][2] = 7;
	mtx->mtx[3][3] = 8;
}

void	print_mtx(t_mtx4 *mtx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			printf("[%.1f]", mtx->mtx[i][j]);
		printf("\n");
	}
}


