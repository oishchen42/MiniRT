/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:26:11 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/19 22:38:18 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <time.h>

void	create_mtx(t_mtx4 *mtx)
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
		}
	}
}

void	print_mtx(t_mtx4 *mtx)
{
	int	i;
	int	j;

	i = -1;
	while (++i)
	{
		j = -1;
		while (++j)
			printf("[%zu]\n", mtx->mtx[i][j]);
	}
}
