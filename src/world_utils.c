/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdietz-r <tdietz-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:06:54 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/16 15:36:05 by tdietz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

// Timo updated function. fixed declaration in same line and inside function
void	wadd_obj(t_world *world, t_light *light, t_obj *obj)
{
	t_list	*node;

	if (obj)
	{
		node = ft_lstnew((void *)obj);
		ft_lstadd_back(&world->objs, node);
	}
	if (light)
	{
		node = ft_lstnew((void *)light);
		ft_lstadd_back(&world->lights, node);
	}
}

t_world	init_world(void)
{
	t_world	w;

	ft_bzero(&w, sizeof(t_world));
	w.objs = NULL;
	w.lights = NULL;
	return (w);
}

void	wclear_world(t_world *world)
{
	ft_lstclear(&world->objs, free);
	ft_lstclear(&world->lights, free);
}
