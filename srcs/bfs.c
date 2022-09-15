/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/15 18:46:19 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* void get_path(t_edge *queue, int q_idx)
{
	int i = q_idx - 1;
	int j;

	while (i > -1)
	{
		if (queue[i].to->state == END_ROOM)
		{
			printf("----/p%d:\n%s-", queue[i].from->path_idx, queue[i].to->name);
			t_room *tar = queue[i].from;
			t_room *tar2 = queue[i].b4from;
			j = i;
			while (j > -1)
			{
				if (queue[j].to == tar && queue[j].from == tar2)
				{
					printf("%s-", queue[j].to->name);
					tar = queue[j].from;
					tar2 = queue[j].b4from;
				}
				j--;
			}
			printf("\n");
		}
		i--;
	}
} */

static int	get_adj(int idx, t_edge *queue, int *q_count)
{
	t_rlist *links;
	t_room	*room;
	t_room	*before;
	int amt;

	room = queue[idx].to;
	before = queue[idx].from;
	links = room->links;
	amt = 0;
	while (links)
	{
		if (links->room->crossed == 0)
		{
			queue[*q_count].b4from = before;
			queue[*q_count].from = room;
			queue[*q_count].to = links->room;
			(*q_count)++;
			amt++;
			if (room->state != START_ROOM) //optimize this (currently checking condition for every single room)
				break;
		}
		links = links->next;
	}
	return (amt);
}

void bfs(t_room *room, int ant)
{
	int	q_rem = 1;
	int	q_count = 1;
	int	q_idx = 0;
	t_edge queue[MAGIC_NUMBER];
	t_path path[MAGIC_NUMBER];
	int path_idx = 0;
	t_path_group best;
	t_path_group cur;

	init_path_groups(&best);
	init_path_groups(&cur);
	queue[0].b4from = room;
	queue[0].from = room;
	queue[0].to = room;
	while (q_rem--)
	{
		//printf("%s - %s - %s\n", queue[q_idx].b4from->name, queue[q_idx].from->name, queue[q_idx].to->name);
		if (queue[q_idx].to->state != END_ROOM)
		{
			if (queue[q_idx].to->crossed == 0)
			{
				queue[q_idx].to->crossed = 1;
				q_rem += get_adj(q_idx, queue, &q_count);
			}
		}
		else
		{
			conclude_path(queue, q_idx, path, path_idx);
			adjust_path_group(&cur, path, &path_idx);
			line_count(&cur, path, ant);
			if (best.line_count > cur.line_count || best.line_count == 0)
				assign_path_group(&best, &cur);
		}
		q_idx++;
	}
	printf("LC: %d\n", best.line_count);
	//get_path(queue, q_idx);
}