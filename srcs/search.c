/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 15:59:03 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

//not occupied
static int	not_occupied(t_room *prev_room)
{
	return (prev_room == NULL);
}

// occupied - BACKWARD flow
static int	occ_backward(int current_flow)
{
	return (current_flow == BACKWARD);
}

// occupiedd - UNUSED_FORWARD flow - BACKWARD flow next
static int	occ_unused_to_backward(int current_flow, int next_flow)
{
	return (current_flow == UNUSED_FORWARD && next_flow == BACKWARD);
}

// occupied - USUNUSED_FORWARD flow - USED_FORWARD flow next - less steps taken
static int	shorter_path(int next_flow, int old_steps, int current_steps)
{
	return (next_flow == USED_FORWARD && old_steps > current_steps);
}

int	search(t_edge **queue, int *q_count, int idx, t_tracer *tracer)
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
				|| shorter_path(forw_edge->flow,
					queue[idx]->to->steps, tracer[idx].steps))
			{
				set_tracer(&tracer[*q_count], idx, tracer[idx].steps + 1);
				queue[(*q_count)++] = forw_edge;
				room_count++;
			}
		}
		forw_edge = forw_edge->next;
	}
	return (room_count);
}
