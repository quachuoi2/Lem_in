/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/05 09:36:03 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//not occupied
int	not_occupied(t_room *prev_room)
{
	return (prev_room == NULL);
}

// occupied - BACKWARD flow
int	occ_backward(int flow)
{
	return (flow == BACKWARD);
}

// occupiedd - UNUSED_FORWARD flow - BACKWARD flow next
int	occ_unused_to_backward(int current_flow, int next_flow)
{
	return (current_flow == UNUSED_FORWARD && next_flow == BACKWARD);
}

// occupied - USUNUSED_FORWARD flow - USED_FORWARD flow next - less steps taken
int	steps(int next_flow, int old_step_count, int current_step_count)
{
	return (next_flow == USED_FORWARD && old_step_count > current_step_count);
}

int	search_forward(t_edge **queue, int *q_count, int idx, t_tracer *tracer)
{
	int		room_count;
	t_edge	*forw_edge;

	room_count = 0;
	forw_edge = queue[idx]->to->edge;
	while (forw_edge)
	{
		if (forw_edge->to != queue[idx]->from)
		{
			if (forw_edge->to == queue[idx]->to->prev)
				forw_edge->flow = BACKWARD;
			if (not_occupied(queue[idx]->to->prev)
				|| occ_backward(queue[idx]->flow)
				|| occ_unused_to_backward(queue[idx]->flow, forw_edge->flow)
				|| steps(forw_edge->flow, queue[idx]->to->step_count, tracer[idx].step_count))
			{
				tracer[*q_count].idx = idx;
				tracer[*q_count].step_count = tracer[idx].step_count + 1;
				queue[(*q_count)++] = forw_edge;
				room_count++;
			}
		}
		forw_edge = forw_edge->next;
	}
	return (room_count);
}
