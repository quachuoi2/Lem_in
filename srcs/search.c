/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/22 19:46:38 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int search_free_link(t_edge **queue, int *q_count, int idx, int *tracer)
{
	int room_count;
	t_rlist *links;

	links = queue[idx]->to->links;
	room_count = 0;
	while (links)
	{
		if (links->forw_list_created == 0)
		{
			links->forw_list_created = 1;
			queue[*q_count] = add_elist(queue[idx]->to, links->room);
			tracer[*q_count] = idx;
			(*q_count)++;
			room_count ++;
		}
		links = links->next;
	}
	return (room_count);
}

int search_forward(t_edge **queue, int *q_count, int idx, int *tracer)
{
	int room_count;

	room_count = 0;
	t_edge	*forw_edge = queue[idx]->to->forward_list;
	while (forw_edge)
	{
		if (forw_edge->to != queue[idx]->from) //dont search the link you just came from
		{
			if (forw_edge->to == queue[idx]->to->prev) // to know if im looking at a forw edge similar to the backward room
				forw_edge->flow = BACKWARD;
			if (queue[idx]->to->prev != 0) //room is occupied
			{
				if (queue[idx]->flow == BACKWARD)
				{
					queue[*q_count] = forw_edge;
					tracer[*q_count] = idx;
					(*q_count)++;
					room_count++;
				}
				if (queue[idx]->flow == UNUSED_FORWARD && forw_edge->flow == BACKWARD) // no exisiting flow
				{
					queue[*q_count] = forw_edge;
					tracer[*q_count] = idx;
					(*q_count)++;
					room_count++;
				}
			}
			else
			{
				queue[*q_count] = forw_edge;
				tracer[*q_count] = idx;
				(*q_count)++;
				room_count++;
			}
		}
		forw_edge = forw_edge->next;
	}
	return (room_count);
}

//category to pass
// current room is NOT occupied aka doesnt have a backward edge (aka room->prev == 0)
// current room is occupied but the flow that lead to current room is a BACKWARD flow
// current room is occupied and the flow that lead to current room is an UNUSED_FORWARD flow, but the flow to the next room is a BACKWARD

//SewDough Code
//	room = queue.to
//	if (room is occupied)
//	{
// 		if flow from queue.from -> queue.to == BACKWARD
// 			then queue.to -> forward can be UNUSED FORWARD or BACKWARD

// 		if flow from queue.from -> queue.to == UNUSED FORWARD
// 			then queue.to -> forward must be BACKWARD
//	}
//	else if (room is NOT occupied)
//		Good to go
