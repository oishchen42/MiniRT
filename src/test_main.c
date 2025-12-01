/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:21:32 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/01 21:04:53 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main()
{
	//t_mtx4	mtx1;
	//t_mtx4	mtx2;
	//t_mtx4	mtx3;
	////t_mtx4	mtx3_cp;

	//t_mtx3	mtx3_test;
	//t_mtx2	sub_mtx;

	//double	determ;

	//printf("CREATION TEST: MTX4\n");
	//create_mtx4_stb(&mtx1);
	//create_mtx4_stb2(&mtx2);
	//print_mtx4(&mtx1);
	//printf("\n");
	//print_mtx4(&mtx2);
	//printf("---------------------------\n");

	//printf("OP TEST: MULTY MTXS4\n");
	//mtx3 = mtxs_mult4(&mtx1, &mtx2);
	//print_mtx4(&mtx3);
	//printf("---------------------------\n");
	
	//printf("CREATION TEST: MTX3\n");
	//create_mtx3_stb(&mtx3_test);
	//print_mtx3(&mtx3_test);
	//printf("---------------------------\n");
	////mtx3_cp = id_mtx(&mtx3);
	////print_mtx(&mtx3_cp);

	//printf("OP TEST: SUBMTX\n");
	//sub_mtx = sub_mtx3(&mtx3_test, 1, 1);
	//print_mtx2(&sub_mtx);
	//printf("---------------------------\n");

	//printf("CREATION TEST: MTX4\n");
	//create_mtx2_stb(&sub_mtx);
	//print_mtx2(&sub_mtx);
	//printf("---------------------------\n");

	//printf("OP TEST: determ_MTX2\n");
	//determ = mtx2_determ(&sub_mtx);
	//printf("determ_mtx2: %f\n", determ);
	//printf("---------------------------\n");

	//printf("OP TEST: determ_MTX2\n");
	//determ = mtx2_determ(&sub_mtx);
	//printf("determ_mtx2: %f\n", determ);
	//printf("---------------------------\n");

	//printf("OP TEST: determ_MTX3\n");
	//create_mtx3_stb(&mtx3_test);
	//determ = mtx3_determ(&mtx3_test);
	//printf("determ_mtx3: %f\n", determ);
	//printf("---------------------------\n");

	//printf("OP TEST: SUBMTX4\n");
	//create_mtx4_stb2(&mtx1);
	//mtx3_test = sub_mtx4(&mtx1, 1, 1);
	//print_mtx3(&mtx3_test);
	//printf("---------------------------\n");

	//printf("OP TEST: determ_MTX4\n");
	//determ = mtx4_determ(&mtx1);
	//printf("determ_mtx3: %f\n", determ);
	//printf("---------------------------\n");

	//printf("OP TEST: inverse_MTX4\n");
	//create_mtx4_stb(&mtx2);
	//mtx1 = mtx4_inverse(&mtx2);
	//print_mtx4(&mtx1);
	//printf("---------------------------\n");

	//printf("OP TEST: MATRIX MUL && INVERSE\n");
	//t_mtx4 A;
	//t_mtx4 B;
	//t_mtx4 AB;
	//create_mtx4_stb(&A);
	//create_mtx4_stb2(&B);
	//print_mtx4(&A);
	//printf("\n");
	//print_mtx4(&B);
	//printf("\n");
	//AB = mtxs_mult4(&A, &B);
	//print_mtx4(&AB);
	//t_mtx4 inv = mtx4_inverse(&A);
	//printf("\n");
	//print_inv4(&inv);
	//printf("\n");
	//t_mtx4 res = mtxs_mult4(&inv, &AB);
	//print_mtx4(&res);
	//printf("---------------------------\n");

	//printf("OP TEST: intersec\n");
	//t_ray	ray = {{0,0,-5, 1}, {0,0,1,0}};
	//t_vcpnt pnt = {2,2,2, 1};
	//t_mtx4	scl_mtx = scale4(&pnt);
	//create_transform_mtx4(&sp.data.sp.transform, &scl_mtx);

	//t_intersec inter = inter_obj(&sp, &ray);
	//if (inter.count > 0)
	//{
	//	printf("root1: %f\n", inter.inter[0]);
	//	printf("root2: %f\n", inter.inter[1]);
	//}
	//printf("---------------------------\n");

	//t_vcpnt orig = {0,0,-5,1};
	//int		canvas = 500;
	//double	wall  = 7.0;
	//double	half = wall / 2;
	//int		i;
	//int		j;
	//double	wall_per_pix = wall / canvas;
	//double	world_x;
	//double	world_y;
	//double	world_z = 10.0;
	//t_obj	sp = sphere();

	//mlx_t	*mlx;
	//mlx_image_t	*img;

	//i = -1;
	//printf("bla\n");
	//if (!(mlx = mlx_init(canvas, canvas, "MLX42", true)))
	//	return (1);
	//printf("bla\n");
	
	//if (!(img = mlx_new_image(mlx, canvas, canvas)))
	//	return (1);
	//if (mlx_image_to_window(mlx, img, 0, 0) == -1)
	//	return (printf("bla\n"), 1);

	//while (++i < canvas)
	//{
	//	j = -1;
	//	world_y = half - (wall_per_pix * i);
	//	while (++j < canvas)
	//	{
	//		world_x = -half + (wall_per_pix * j);
	//		t_vcpnt	target = {world_x, world_y, world_z, 1};
	//		t_vcpnt dir = vec_subs(&target, &orig);
	//		dir = vec_norm(&dir);
	//		t_ray r = {orig, dir};
	//		t_intersec	*inter = inter_obj(&sp, &r);
	//		if (!inter)
	//			return (printf("no inter\n"), 1);
	//		if ((hit(inter)))
	//		{
	//			mlx_put_pixel(img, i, j, get_rgba(255, 0, 0, 255));
	//		}
	//		else
	//			mlx_put_pixel(img, i, j, get_rgba(0,0,0,255));
	//		free_inter(inter->next);
	//		free_inter(inter);
	//	}
	//}
	//mlx_loop(mlx);
	//mlx_terminate(mlx);

	//return (0);

	t_mtx4 mtx = {
			{
				{0,5,3,0},
				{4,1,8,9},
				{6,3,0,2},
				{2,7,1,9}
			}
		};
	t_mtx4 transp = transpose(&mtx);
	print_mtx4(&transp);
}