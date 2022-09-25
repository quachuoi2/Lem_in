/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:44:32 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/24 20:01:04 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_flow(t_edge *list, t_room *target_room, int flow)
{
	while (list && list->to != target_room) //loop to forward links to find the room to remove flow
		list = list->next;
	list->flow = flow;
}

void	delete_residual(t_room *room)//room = edge->from
{
	set_flow(room->forward_list, room->next, UNUSED_FORWARD);
	room->next = 0;
}

void	remove_old_longer_path(t_room *room)
{
	t_room	*temp;
	t_room	*final;

	while (room->state != START_ROOM)
	{
		final = temp;
		temp = room->prev;
		delete_residual(room->prev);
		room->prev = 0;
		room = temp;
	}
	set_flow(room->forward_list, final, UNUSED_FORWARD);
}

void	update_step_count(t_room *room)
{
	while (room->state != END_ROOM)
	{
		room->step_count = room->prev->step_count + 1;
		room = room->next;
	}
}
