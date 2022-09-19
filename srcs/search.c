/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/18 21:35:57 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_unoccupied_link(t_rlist *links, t_edge **queue, int *q_count, int idx)
{
	if (links->room->occupied == UNOCCUPIED
		&& links->room->visited != VISITED
			&& links->room->state != END_ROOM)
	{
		queue[*q_count] = add_elist(queue[idx]->to, links->room);
		(*q_count)++;
		return (1);
	}
	return (0);
}

static int	check_unvisited_link(t_rlist *links, t_edge **queue, int *q_count, int idx)
{
	if (links->room->visited != VISITED)
	{
		queue[*q_count] = add_elist(queue[idx]->to, links->room);
		(*q_count)++;
		return (1);
	}
	return (0);
}

int search_free_link(t_edge **queue, int *q_count, int idx, int unvisited_or_unoccupied)
{
	int mt_room_count;
	t_rlist *links;

	links = queue[idx]->to->links;
	mt_room_count = 0;
	while (links)
	{
		if (unvisited_or_unoccupied == UNVISITED)
			mt_room_count += check_unvisited_link(links, queue, q_count, idx);
		else
			mt_room_count += check_unoccupied_link(links, queue, q_count, idx);
		links = links->next;
	}
	return (mt_room_count);
}

int	search_backward(t_edge **queue, int *q_count, int idx)
{
	int mt_room_count;
	t_room *current_room;

	//search through links for non-occupied room
	mt_room_count = search_free_link(queue, q_count, idx, UNOCCUPIED);

	//otherwise search backward edge for occupied/nonvisited room
	if (!mt_room_count)
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
	return (mt_room_count);
}

int search_forward(t_edge **queue, int *q_count, int idx)
{
	int mt_room_count;

	mt_room_count = 0;
	t_edge	*temp = queue[idx]->to->forward_list;
	while (temp)
	{
		if (temp->flow == 0)
		{
			queue[*q_count] = temp;
			(*q_count)++;
			mt_room_count++;
		}
		temp = temp->next;
	}
	return (mt_room_count);
}
