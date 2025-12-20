/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_supp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 05:55:20 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/20 05:56:03 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_master	init_master(void)
{
	t_master	mstr;

	mstr.world = init_world();
	mstr.split = NULL;
	mstr.cur_line = NULL;
	mstr.amb.is_amb = 0;
	mstr.o_fd = -1;
	mstr.counts.amb_count = 0;
	mstr.counts.cam_count = 0;
	mstr.counts.light_count = 0;
	return (mstr);
}
