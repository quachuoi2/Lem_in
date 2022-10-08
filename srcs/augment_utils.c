/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:44:32 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 09:42:16 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_flow(t_edge *list, t_room *target_room, int flow)
{
	while (list && list->to != target_room)
		list = list->next;
	list->flow = flow;
}

void	delete_forward_room(t_room *room)
{
	set_flow(room->edge, room->next, UNUSED_FORWARD);
	room->next = 0;
}

void	delete_prev_room(t_room *room)
{
	set_flow(room->edge, room->prev, UNUSED_FORWARD);
	room->prev = 0;
}

void	remove_old_longer_path(t_room *room)
{
	t_room	*temp;
	t_room	*final;

	while (room != g_source)
	{
		final = temp;
		temp = room->prev;
		delete_forward_room(room->prev);
		delete_prev_room(room);
		room = temp;
	}
	set_flow(room->edge, final, UNUSED_FORWARD);
}
