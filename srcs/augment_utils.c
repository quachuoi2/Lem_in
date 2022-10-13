/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:44:32 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/13 13:08:38 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	set_flow(t_edge *list, t_room *target_room, int flow)
{
	if (target_room != NULL)
	{
		while (list && list->to != target_room)
			list = list->next;
		list->flow = flow;
	}
}

void	delete_forward_room(t_room *room)
{
	set_flow(room->edge, room->next, UNUSED);
	room->next = 0;
}

void	delete_prev_room(t_room *room)
{
	set_flow(room->edge, room->prev, UNUSED);
	room->prev = 0;
}

void	remove_old_longer_path(t_room *room)
{
	t_room	*temp;
	t_room	*final;

	final = NULL;
	temp = NULL;
	while (room != g_source)
	{
		final = temp;
		temp = room->prev;
		delete_forward_room(room->prev);
		delete_prev_room(room);
		room = temp;
	}
	set_flow(room->edge, final, UNUSED);
}
