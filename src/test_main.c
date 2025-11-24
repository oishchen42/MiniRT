/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:21:32 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/24 16:07:44 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

int	main()
{
	t_mtx4	mtx1;
	t_mtx4	mtx2;
	t_mtx4	mtx3;
	//t_mtx4	mtx3_cp;

	t_mtx3	mtx3_test;
	t_mtx2	sub_mtx;

	double	determ;

	printf("CREATION TEST: MTX4\n");
	create_mtx4_stb(&mtx1);
	create_mtx4_stb2(&mtx2);
	print_mtx4(&mtx1);
	printf("\n");
	print_mtx4(&mtx2);
	printf("---------------------------\n");

	printf("OP TEST: MULTY MTXS4\n");
	mtx3 = mtxs_mult4(&mtx1, &mtx2);
	print_mtx4(&mtx3);
	printf("---------------------------\n");
	
	printf("CREATION TEST: MTX3\n");
	create_mtx3_stb(&mtx3_test);
	print_mtx3(&mtx3_test);
	printf("---------------------------\n");
	//mtx3_cp = id_mtx(&mtx3);
	//print_mtx(&mtx3_cp);

	printf("OP TEST: SUBMTX\n");
	sub_mtx = sub_mtx3(&mtx3_test, 1, 1);
	print_mtx2(&sub_mtx);
	printf("---------------------------\n");

	printf("CREATION TEST: MTX4\n");
	create_mtx2_stb(&sub_mtx);
	print_mtx2(&sub_mtx);
	printf("---------------------------\n");

	printf("OP TEST: determ_MTX2\n");
	determ = mtx2_determ(&sub_mtx);
	printf("determ_mtx2: %f\n", determ);
	printf("---------------------------\n");

	printf("OP TEST: determ_MTX2\n");
	determ = mtx2_determ(&sub_mtx);
	printf("determ_mtx2: %f\n", determ);
	printf("---------------------------\n");

	printf("OP TEST: determ_MTX3\n");
	create_mtx3_stb(&mtx3_test);
	determ = mtx3_determ(&mtx3_test);
	printf("determ_mtx3: %f\n", determ);
	printf("---------------------------\n");

	printf("OP TEST: SUBMTX4\n");
	create_mtx4_stb2(&mtx1);
	mtx3_test = sub_mtx4(&mtx1, 1, 1);
	print_mtx3(&mtx3_test);
	printf("---------------------------\n");

	printf("OP TEST: determ_MTX4\n");
	determ = mtx4_determ(&mtx1);
	printf("determ_mtx3: %f\n", determ);
	printf("---------------------------\n");

	printf("OP TEST: inverse_MTX4\n");
	create_mtx4_stb(&mtx2);
	mtx1 = mtx4_inverse(&mtx2);
	print_mtx4(&mtx1);
	printf("---------------------------\n");

	printf("OP TEST: MATRIX MUL && INVERSE\n");
	t_mtx4 A;
	t_mtx4 B;
	t_mtx4 AB;
	create_mtx4_stb(&A);
	create_mtx4_stb2(&B);
	print_mtx4(&A);
	printf("\n");
	print_mtx4(&B);
	printf("\n");
	AB = mtxs_mult4(&A, &B);
	print_mtx4(&AB);
	t_mtx4 inv = mtx4_inverse(&A);
	printf("\n");
	print_inv4(&inv);
	printf("\n");
	t_mtx4 res = mtxs_mult4(&inv, &AB);
	print_mtx4(&res);
	printf("---------------------------\n");

	printf("OP TEST: TRANSLATION INV\n");
	t_vcpnt vp = {5, -3, 2, 0};
	get_empty_mtx4(&A);
	translation4(&vp, &A);
	print_mtx4(&A);
	double dtrm = mtx4_determ(&A);
	printf("determ: %f\n", dtrm);
	inv = mtx4_inverse(&A);
	print_inv4(&inv);
	printf("---------------------------\n");

	printf("OP TEST: TRANSFORM\n");
	t_vcpnt pnt = {-3, 4, 5, 0};
	t_vcpnt	new_ptr = {2, 1, 0, 1};
	t_mtx4 trans_pnt;
	get_empty_mtx4(&trans_pnt);
	translation4(&pnt, &trans_pnt);
	new_ptr = transform4(&new_ptr, &trans_pnt);
	print_vpnt4(&new_ptr);
	printf("---------------------------\n");

	return (0);
}