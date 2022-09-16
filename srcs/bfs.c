/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/16 11:13:21 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void print_all_path(t_room *room)
{
	t_room *temp;

	while (room->links)
	{
		if (room->links->room->edge)
		{
			temp = room->links->room;
			printf("%s - ", temp->edge->from->name);
			while (temp->state != END_ROOM)
			{
				printf("%s - ", temp->name);
				temp = temp->edge->to;
			}
			printf("%s\n", temp->name);
		}
		room->links = room->links->next;
	}
}

void conclude_path(t_edge *rev_queue, int revq_idx, t_path *path, int path_idx)
{
	int step_count;
	t_room *current_tar;

	step_count = 0;
	current_tar = rev_queue[revq_idx - 1].to;
	printf("---\n");
	printf("%s - ", rev_queue[revq_idx - 1].from->name);
	printf("%s - ", current_tar->name);
	while (rev_queue[--revq_idx].to->state != START_ROOM)
	{
		if (rev_queue[revq_idx].from == current_tar)
		{
			printf("%s - ", rev_queue[revq_idx].to->name);
			current_tar = rev_queue[revq_idx].to;
		}
		step_count++;
	}
	printf("%s\n", rev_queue[revq_idx].to->name);
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
		if (links->room->crossed == 0)
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
	t_edge queue[MAGIC_NUMBER];
	t_edge rev_queue[MAGIC_NUMBER];
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
			if (queue[q_idx].to->crossed == 0)
			{
				queue[q_idx].to->crossed = 1;
				assign_rev_queue(&rev_queue[revq_idx], &queue[q_idx]);
				revq_idx++;
				q_rem += get_adj(queue, &q_count, q_idx);
			}
		}
		else
		{
			assign_rev_queue(&rev_queue[revq_idx], &queue[q_idx]);
			revq_idx++;
			conclude_path(rev_queue, revq_idx, path, path_idx);
			adjust_path_group(&cur, path, &path_idx);
			line_count(&cur, path, ant);
			if (best.line_count > cur.line_count || best.line_count == 0)
				assign_best_group(&best, &cur);
		}
		q_idx++;
	}
	// print_all_path(room);
	// printf("%d\n", best.group[0]);
	printf("LC: %d\n", best.line_count);
}