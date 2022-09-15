/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/15 20:43:53 by qnguyen          ###   ########.fr       */
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
			printf("----/p%d:\n%s-", queue[i].current->path_idx, queue[i].to->name);
			t_room *current_tar = queue[i].current;
			t_room *b4_tar = queue[i].b4from;
			j = i;
			while (j > -1)
			{
				if (queue[j].to == current_tar && queue[j].current == b4_tar)
				{
					printf("%s-", queue[j].to->name);
					current_tar = queue[j].current;
					b4_tar = queue[j].b4from;
				}
				j--;
			}
			printf("\n");
		}
		i--;
	}
} */

void	conclude_path(t_edge *queue, int q_idx, t_path *path, int path_idx)
{
	int	step_count;
	t_room	*current_tar;
	t_room	*b4_tar;

	step_count = 0;
	current_tar = queue[q_idx].current;
	b4_tar = queue[q_idx].b4from;
	queue[q_idx].current->edge = &queue[q_idx]; //assign current edge to current room
	while (--q_idx > -1)
	{
		if (queue[q_idx].current == b4_tar && queue[q_idx].to == current_tar)
		{
			/* if (queue[q_idx].to->state != START_ROOM)
				queue[q_idx].to->path_idx = path_idx; */
			current_tar = queue[q_idx].current;
			b4_tar = queue[q_idx].b4from;
			queue[q_idx].current->edge = &queue[q_idx];  //assign current edge to current room
			step_count++;
		}
	}
	path[path_idx].steps = step_count;
	path[path_idx].ant_count = 0;
}

static int	get_adj(int idx, t_edge *queue, int *q_count)
{
	t_rlist *links;
	t_room	*room;
	t_room	*before;
	int amt;

	room = queue[idx].to;
	before = queue[idx].current;
	links = room->links;
	amt = 0;
	while (links)
	{
		if (links->room->crossed == 0)
		{
			queue[*q_count].b4from = before;
			queue[*q_count].current = room;
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

static void	print_all_path(t_room *room)
{
	t_room *temp;

	while (room->links)
	{
		if (room->links->room->edge)
		{
			temp = room->links->room;
			printf("%s - ", temp->edge->b4from->name);
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

void bfs(t_room *room, int ant)
{
	int	q_rem = 1;
	int	q_count = 1;
	int	q_idx = 0;
	int path_idx = 0;
	t_edge queue[MAGIC_NUMBER];
	t_path path[MAGIC_NUMBER];
	t_path_group best;
	t_path_group cur;

	init_path_groups(&best);
	init_path_groups(&cur);
	queue[0].b4from = room;
	queue[0].current = room;
	queue[0].to = room;
	while (q_rem--)
	{
		//printf("%s - %s - %s\n", queue[q_idx].b4from->name, queue[q_idx].current->name, queue[q_idx].to->name);
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
	//print_all_path(room);
	printf("LC: %d\n", best.line_count);
}