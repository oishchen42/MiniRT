/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_mv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:51:30 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/17 23:44:05 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

//void my_mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
//{
//	t_master *app = (t_master *)param;
//	(void)mods;

//	if (button == MLX_MOUSE_BUTTON_MIDDLE)
//	{
//		if (action == MLX_PRESS)
//		{
//			app->is_dragging = true;
//			// Capture the starting position immediately so we don't jump
//			mlx_get_mouse_pos(app->mlx, (int32_t*)&app->last_mouse_x, (int32_t*)&app->last_mouse_y);
//		}
//		else if (action == MLX_RELEASE)
//		{
//			app->is_dragging = false;
//		}
//	}
//}

// Helper to move both 'from' and 'to' by a vector
