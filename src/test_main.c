/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:21:32 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/08 22:18:16 by oishchen         ###   ########.fr       */
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

	//t_vcpnt orig = {0,0,-35,1};
	//int		canvas = 1000;
	//double	wall  = 15.0;
	//double	half = wall / 2;
	//int		i;
	//int		j;
	//double	wall_per_pix = wall / canvas;
	//double	world_x;
	//double	world_y;
	//double	world_z = 40.0;
	//t_obj	*sp = sphere(NULL);
	
	//t_light	light;

	//mlx_t	*mlx;
	//mlx_image_t	*img;

	//t_intersec	*winner_inter;

	//i = -1;
	//light.intens = (t_vcpnt){1,1,1,1};
	//light.pnt_light = (t_vcpnt){-10,10,-10,1};
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
	//		//if (i == 490 && j == 490) 
	//		//	print_vpnt4(&dir);
	//		dir = vec_norm(&dir);
	//		t_ray r = {orig, dir};
	//		//t_vcpnt	scalev = {3, 1.5, 1, 0};
	//		//t_mtx4	new_trans = scale4(&scalev);
	//		//create_transform_mtx4(&sp->data.sp.transform, &new_trans);
	//		t_intersec	*inter = inter_obj(sp, &r);
	//		if (!inter)
	//			return (printf("no inter\n"), 1);
	//		if ((winner_inter = hit(inter)))
	//		{
	//			t_vcpnt scaled_vec = vec_scale(&r.vec, winner_inter->t);
	//			t_vcpnt hit_point = vec_add(&r.pnt, &scaled_vec);
	//			t_vcpnt eye_vec = vec_scale(&r.vec, -1);
	//			t_vcpnt normv = normal_at(&sp->data.sp, &hit_point);
	//			t_vcpnt color = lighting(&sp->data.sp.mat, &light, &hit_point, &eye_vec, &normv);
	//			mlx_put_pixel(img, j, i, vcpnt_2_rgba(&color));
	//		}
	//		else
	//			mlx_put_pixel(img, j, i, get_rgba(0,0,0,255));
	//		free_inter(inter->next);
	//		free_inter(inter);
	//	}
	//}
	//free(sp);
	//mlx_loop(mlx);
	//mlx_terminate(mlx);

	//return (0);

	//t_mtx4 mtx = {
	//		{
	//			{0,5,3,0},
	//			{4,1,8,9},
	//			{6,3,0,2},
	//			{2,7,1,9}
	//		}
	//	};
	//t_mtx4 transp = transpose(&mtx);
	//print_mtx4(&transp);
	//t_obj sp;

	//sp = sphere();
	//t_vcpnt vec_to_scale = {1,0.5,1, 0};
	//t_mtx4 mtx = scale4(&vec_to_scale);
	//t_mtx4 rot = rotate_z(PI/5);
	//t_mtx4 mult = mtxs_mult4(&mtx, &rot);
	//create_transform_mtx4(&sp.data.sp.transform, &mult);
	//print_mtx4(&sp.data.sp.transform);
	//t_vcpnt	nrm = {0, sqrt(2) / 2, -1 * sqrt(2) / 2, 0};
	//t_vcpnt n = normal_at(&sp.data.sp, &nrm);
	//print_vpnt4(&n);

	//printf("TEST OF LIGHTING\n");
	//t_obj sp;

	//sp = sphere();
	//t_vcpnt	eye = {0,0,-1,1};
	//t_vcpnt	position = {0,0,0,1};
	//t_vcpnt	normalv = {0,0,-1,1};
	//t_light	light;
	//light.intens = (t_vcpnt){1,1,1,1};
	//light.pnt_light = (t_vcpnt){0,0,10,1};
	//t_vcpnt	result = lighting(&sp.data.sp.mat, &light, &position, &eye, &normalv);
	//print_vpnt4(&result);

	//t_matirial mat;

	//t_vcpnt	mat_color = {0.8, 1.0, 0.6, 0};
	//double	diffuse = 0.7;
	//double	specular = 0.2;
	//mat = create_mat(&mat_color, diffuse, specular);

	//printf("RENDARING THE WORLD (SOUNDS FROM THE STAR WARS:\n PA-PA-PA-PAAAAA-PAAAA\n");
	//t_vcpnt orig = {0,0,-5,1};

	//t_matirial mat;
	//mat.ambient = 0.1;
	//mat.color = (t_vcpnt){0.8, 1.0, 0.6, 1};
	//mat.diffuse = 0.7;
	//mat.specular = 0.2;
	//t_obj	*sp = sphere(&mat);
	//t_obj	*sp1 = sphere(NULL);
	//t_vcpnt	scalev = {0.5, 0.5, 0.5, 0};
	//sp1->data.sp.transform = scale4(&scalev);

	//t_world	world;

	//world = init_world();
	//wadd_obj(&world, NULL, sp);
	//printf("pixel_start\n");
	//wadd_obj(&world, NULL, sp1);

	//t_vcpnt	intens = (t_vcpnt){1, 1, 1 ,1};
	//t_vcpnt	pnt_light = (t_vcpnt){-10,10,-10,1};
	//t_light	*light = create_light(&pnt_light, &intens);
	//wadd_obj(&world, light, NULL);

	//t_vcpnt	dir = {0,0,1,1};
	//dir = vec_norm(&dir);
	//t_ray r = {orig, dir};
	//world_inter(&world, &r);
	//wclear_world(&world);
	//printf("finish\n");

	printf("test for the new shorter light function\n");
	t_vcpnt orig = {0,0,-5,1};

	t_matirial mat;
	mat.ambient = 0.1;
	mat.color = (t_vcpnt){0.8, 1.0, 0.6, 1};
	mat.diffuse = 0.7;
	mat.specular = 0.2;
	t_obj	*sp = sphere(&mat);
	t_obj	*sp1 = sphere(NULL);
	t_vcpnt	scalev = {0.5, 0.5, 0.5, 0};
	sp1->data.sp.transform = scale4(&scalev);

	t_world	world;

	world = init_world();
	wadd_obj(&world, NULL, sp);
	printf("pixel_start\n");
	wadd_obj(&world, NULL, sp1);

	t_vcpnt	intens = (t_vcpnt){1, 1, 1 ,1};
	t_vcpnt	pnt_light = (t_vcpnt){-10,10,-10,1};
	t_light	*light = create_light(&pnt_light, &intens);
	wadd_obj(&world, light, NULL);

	t_vcpnt	dir = {0,0,1,1};
	dir = vec_norm(&dir);
	t_ray r = {orig, dir};
	t_vcpnt res = world_inter(&world, &r);
	print_vpnt4(&res);

	wclear_world(&world);
	printf("finish\n");

	return (0);
}