/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/22 01:47:41 by qnguyen          ###   ########.fr       */
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
		if (links->forw_list_created == 0)
		{
			links->forw_list_created = 1;
			queue[*q_count] = add_elist(queue[idx]->to, links->room);
			(*q_count)++;
			room_count ++;
		}
		links = links->next;
	}
	return (room_count);
}

int search_forward(t_edge **queue, int *q_count, int idx)
{
	int room_count;

	room_count = 0;
	t_edge	*edge = queue[idx]->to->forward_list;
	while (edge)
	{
		if (edge->flow != USED_FORWARD) // no exisiting flow //one change here today
		{
			if (edge->to == queue[idx]->to->prev) // to know if im looking at a forw edge similar to the backward one
				edge->flow = BACKWARD;
			queue[*q_count] = edge;
			(*q_count)++;
			room_count++;
		}
		edge = edge->next;
	}
	return (room_count);
}
