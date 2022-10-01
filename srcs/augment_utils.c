/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augment_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 19:44:32 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/30 05:32:36 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_flow(t_edge *list, t_room *target_room, int flow)
{
	while (list && list->to != target_room) //loop to forward links to find the room to remove flow
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

	while (room->state != START_ROOM)
	{
		final = temp;
		temp = room->prev;
		delete_forward_room(room->prev);
		delete_prev_room(room);
		room = temp;
	}
	set_flow(room->edge, final, UNUSED_FORWARD);
}

void	update_step_count(t_edge *rev_edge, int i, int rev_idx)
{
	t_room	*room;
	int		room_count;

	room = rev_edge[i].from->next;
	room_count = rev_edge[i].from->step_count + 1;
	while (room->state != END_ROOM)
	{
		// printf("%s\n", room->name);
		room->step_count = room_count;
		room_count++;
		room = room->next;
	}
	// printf("%s\n", room->name);
	rev_edge[rev_idx].from->path_steps = room_count; //set path count for new path
}
