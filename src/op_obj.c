/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 22:32:46 by oishchen          #+#    #+#             */
/*   Updated: 2025/11/24 22:43:22 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

t_spere	sphere(void)
{
	t_spere	sp;
	t_vcpnt	orig_point;
	
	sp.orig.vp[0] = 0.0;
	sp.orig.vp[1] = 0.0;
	sp.orig.vp[2] = 0.0;
	sp.orig.vp[3] = 1.0;
	sp.radi = 1.0;
	return (sp);
}