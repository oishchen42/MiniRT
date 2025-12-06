/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oishchen <oishchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:06:54 by oishchen          #+#    #+#             */
/*   Updated: 2025/12/06 19:23:15 by oishchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	add_obj(t_world *world, t_light *light, t_obj *obj)
{
	if (obj)
	{
		t_list	*new = ft_lstnew((void *)obj);
		ft_lstadd_back(&world->objs, new);
	}
	if (light)
	{
		t_list	*list_new = ft_lstnew((void *)light);
		ft_lstadd_back(&world->lights, list_new);
	}
}

t_world	init_world(void)
{
	t_world w;

	w.objs = NULL;
	w.lights = NULL;
	return (w);
}

void	clear_obj(t_world *world)
{
	ft_lstclear(&world->objs, free);
}