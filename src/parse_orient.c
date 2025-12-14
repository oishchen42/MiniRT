/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_orient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:28:35 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/14 16:19:55 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_mtx4  get_rotation_matrix(t_vcpnt orientation)
{
	t_mtx4  mtx;
	t_vcpnt new_y;
	t_vcpnt new_x;
	t_vcpnt new_z;
	t_vcpnt guide;

	// 1. The input vector becomes our "New Y" (where the cylinder points)
	new_y = vec_norm(&orientation);

	if (fabs(new_y.vp[0]) < EPSILON && fabs(new_y.vp[2]) < EPSILON)
	{
		get_id_mtx4(&mtx);
		if (new_y.vp[1] < 0) 
			mtx.mtx[1][1] = -1; // Flip upside down if 0,-1,0
		return (mtx);
	}

	// 3. Create a temporary guide vector (World Up)
	guide = (t_vcpnt){0, 1, 0, 0};

	// 4. Calculate New X (Right) = Cross(New Y, Guide)
	new_x = vec_cross(&new_y, &guide);
	new_x = vec_norm(&new_x);

	// 5. Calculate New Z (Forward) = Cross(New X, New Y)
	new_z = vec_cross(&new_x, &new_y);
	new_z = vec_norm(&new_z);

	// 6. Fill the Matrix (Column-Major or Row-Major depending on your math lib)
	// Assuming standard [row][col] with translation in col 3:
	get_id_mtx4(&mtx);

	// First Column (X axis)
	mtx.mtx[0][0] = new_x.vp[0];
	mtx.mtx[1][0] = new_x.vp[1];
	mtx.mtx[2][0] = new_x.vp[2];

	// Second Column (Y axis - Our Orientation)
	mtx.mtx[0][1] = new_y.vp[0];
	mtx.mtx[1][1] = new_y.vp[1];
	mtx.mtx[2][1] = new_y.vp[2];

	// Third Column (Z axis)
	mtx.mtx[0][2] = new_z.vp[0];
	mtx.mtx[1][2] = new_z.vp[1];
	mtx.mtx[2][2] = new_z.vp[2];

	return (mtx);
}

void	pr_cm_orient(t_camera *cam, t_vcpnt pos, t_vcpnt dir, double par_fov_d)
{
	t_vcpnt parsed_pos = {-50.0, 0, 20, 1};
	t_vcpnt parsed_dir = {0, 0, 1, 0};
	double  parsed_fov_deg = 70.0;

	cam->from = parsed_pos;

	// 2. Set "To" Point (Look At)
	// Logic: If I stand at 'pos' and look in 'dir', I am looking at 'pos + dir'
	cam->to = vec_add(&parsed_pos, &parsed_dir);
	cam->to.vp[3] = 1.0; // Ensure it is a point

	// 3. Set "Up" Vector (Hardcoded Default)
	// Check for the parallel edge case!
	if (fabs(parsed_dir.vp[0]) < EPSILON && fabs(parsed_dir.vp[2]) < EPSILON)
	{
		// If looking straight up/down, we can't use Y as up. Use Z or X.
		cam->up = (t_vcpnt){0, 0, 1, 0}; 
	}
	else
	{
		// Standard "World Up"
		cam->up = (t_vcpnt){0, 1, 0, 0}; 
	}

	// 4. Set FOV (Convert Degrees to Radians)
	cam->field_of_view = parsed_fov_deg * (PI / 180.0);

	// 5. Apply
	setup_camera(cam, cam->hsize, cam->vsize, cam->field_of_view); // should be set
}
