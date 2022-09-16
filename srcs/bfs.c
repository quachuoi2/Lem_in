/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/16 15:57:31 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	augment(t_edge **rev_edge, int i)
{
	t_room	*room;

	printf("%s-", rev_edge[i]->to->name);
	while (i > 0)
	{
		room = rev_edge[i]->from;

		room->forward = ft_memalloc(sizeof(t_edge));
		room->forward->to = rev_edge[i - 1]->from;
		room->forward->from = room;
		room->forward->flow = 1;

		room->backward = ft_memalloc(sizeof(t_edge));
		room->backward->to = rev_edge[i]->to;
		room->backward->from = room;
		room->backward->flow = -1;

		printf("%s-", rev_edge[i]->from->name);
		i--;
	}
	printf("%s\n", rev_edge[i]->from->name);
}

void conclude_path(t_edge *rev_queue, int revq_idx, t_path *path, int path_idx)
{
	int step_count;
	int j = 0;
	t_room *current_tar;
	t_edge *rev_edge[revq_idx];

	step_count = 1;
	current_tar = rev_queue[revq_idx].to;
	rev_edge[j++] = &rev_queue[revq_idx];
	while (rev_queue[revq_idx].from->state != START_ROOM)
	{
		if (rev_queue[revq_idx].from == current_tar)
		{
			rev_edge[j++] = &rev_queue[revq_idx];
			current_tar = rev_queue[revq_idx].to;
			step_count++;
		}
		revq_idx--;
	}
	augment(rev_edge, j - 1);
	path[path_idx].steps = step_count;
	path[path_idx].ant_count = 0;
}

static int get_adj(t_edge *queue, int *q_count, int idx)
{
	t_rlist *links;
	int amt;

	links = queue[idx].to->links;
	amt = 0;
	while (links)
	{
		if (links->room->occupied == 0)
		{
			queue[*q_count].from = queue[idx].to;
			queue[*q_count].to = links->room;
			(*q_count)++;
			amt++;
			if (queue[idx].to->state != START_ROOM) // optimize this (currently checking condition for every single room)
				break;
		}
		links = links->next;
	}
	return (amt);
}

void bfs(t_room *room, int ant)
{
	int q_rem = 1;
	int q_count = 1;
	int q_idx = 0;
	int revq_idx = 0;
	int path_idx = 0;
	t_edge *queue = (t_edge *)ft_memalloc(sizeof(t_edge) * MAGIC_NUMBER);
	t_edge *rev_queue = (t_edge *)ft_memalloc(sizeof(t_edge) * MAGIC_NUMBER);;
	t_path path[MAGIC_NUMBER];
	t_path_group best;
	t_path_group cur;

	init_path_groups(&best);
	init_path_groups(&cur);
	queue[0].from = room;
	queue[0].to = room;
	while (q_rem--)
	{
		if (queue[q_idx].to->state != END_ROOM)
		{
			// printf("%s - %s\n", queue[q_idx].from->name, queue[q_idx].to->name);
			if (queue[q_idx].to->occupied == 0)
			{
				queue[q_idx].to->occupied = 1;
				assign_rev_queue(&rev_queue[revq_idx], &queue[q_idx]);
				revq_idx++;
				q_rem += get_adj(queue, &q_count, q_idx);
			}
		}
		else
		{
			assign_rev_queue(&rev_queue[revq_idx], &queue[q_idx]);
			conclude_path(rev_queue, revq_idx, path, path_idx);
			adjust_path_group(&cur, path, &path_idx);
			line_count(&cur, path, ant);
			if (best.line_count > cur.line_count || best.line_count == 0)
			 	assign_best_group(&best, &cur);
		}
		q_idx++;
	}
	printf("LC: %d\n", best.line_count);
}