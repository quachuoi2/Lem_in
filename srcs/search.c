/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/19 12:17:12 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int search_free_link(t_edge **queue, int *q_count, int idx)
{
	int room_count;
	t_rlist *links;

	links = queue[idx]->to->links;
	room_count = 0;
	while (links)
	{
		if (links->room->visited != VISITED)
		{
			queue[*q_count] = add_elist(queue[idx]->to, links->room);
			(*q_count)++;
			room_count ++;
		}
		links = links->next;
	}
	return (room_count);
}

int	search_backward(t_edge **queue, int *q_count, int idx)
{
	int room_count;
	t_room *current_room;

	//search forward links for zero flow edge (aka non-occupied room)
	room_count = search_forward(queue, q_count, idx);
	//otherwise search backward edge for occupied/nonvisited room
	if (room_count == 0)
	{
		current_room = queue[idx]->to;
		if (current_room->backward->to->visited != VISITED)
		{
			queue[*q_count] = current_room->backward;
			//queue[*q_count]->flow = -1;
			(*q_count)++;
		}
		return (1);
	}
	return (room_count);
}

int search_forward(t_edge **queue, int *q_count, int idx)
{
	int room_count;

	room_count = 0;
	t_edge	*temp = queue[idx]->to->forward_list;
	while (temp)
	{
		if (temp->flow == 0)
		{
			queue[*q_count] = temp;
			(*q_count)++;
			room_count++;
		}
		temp = temp->next;
	}
	return (room_count);
}
