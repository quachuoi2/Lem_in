/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/24 17:45:01 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int search_free_link(t_edge **queue, int *q_count, int idx, t_counter *tracer)
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
			tracer[*q_count].idx = idx;
			tracer[*q_count].step_count = tracer[idx].step_count + 1;
			(*q_count)++;
			room_count ++;
		}
		links = links->next;
	}
	return (room_count);
}

int search_forward(t_edge **queue, int *q_count, int idx, t_counter *tracer)
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
			if (queue[idx]->to->prev == 0	//not occupied
				|| (queue[idx]->flow == BACKWARD	// occupied - using BACKWARD flow
				|| (queue[idx]->flow == UNUSED_FORWARD && forw_edge->flow == BACKWARD) // occupeid - using UNUSED_FORWARD flow - going to use BACKWARD flow next
				|| (forw_edge->flow == USED_FORWARD && queue[idx]->to->step_count > tracer[idx].step_count))) // occupied - using USUNUSED_FORWARD flow - going to use USED_FORWARD flow next - steps taken is shorter than augmented steps
				{
					queue[*q_count] = forw_edge;
					tracer[*q_count].idx = idx;
					tracer[*q_count].step_count = tracer[idx].step_count + 1;
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
// current room is occupied BUT the flow that lead to current room is a BACKWARD flow
// current room is occupied AND the flow that lead to current room is an UNUSED_FORWARD flow, BUT the flow to the next room is a BACKWARD
// current room is occupied AND the flow that lead to current room is an UNUSED_FORWARD flow AND the flow to the next room is a USED_FORWARD, but the steps it takes to the current room on this path is less than the augmented path

//SewDough Code
//	room = queue.to
//	if (room is occupied)
//	{
// 		if flow from queue.from -> queue.to == BACKWARD
// 			then queue.to -> forward can be UNUSED FORWARD or BACKWARD

// 		if flow from queue.from -> queue.to == UNUSED FORWARD
// 			if queue.to -> forward is BACKWARD
//				Good to goto
//			if queue.to -> forward is USED_FORWARD
//				if room's step_count (augmented) > current path's step count
//				Good to go
//	}
//	else if (room is NOT occupied)
//		Good to go
