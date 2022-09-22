/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:26:07 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/22 19:35:40 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_path_groups(t_path_group *group)
{
	group->tol_step = 0;
	group->path_count = 0;
	group->line_count = 0;
	group->group = ft_memalloc(sizeof(int) * MAGIC_NUMBER);
}

void	adjust_path_group(t_path_group *cur, t_path *path, int *path_idx)
{
	cur->group[cur->path_count] = *path_idx;
	cur->tol_step += path[*path_idx].steps;
	cur->path_count++;
	(*path_idx)++;
}

void	assign_best_group(t_path_group *best, t_path_group *cur)
{
	int	i;

	best->line_count = cur->line_count;
	best->path_count = cur->path_count;
	best->tol_step = cur->tol_step;
	i = 0;
	while (i < best->path_count)
	{
		best->group[i] = cur->group[i];
		i++;
	}
}

static void	unset_flow(t_edge *list, t_room *target_room)
{
	while (list->to != target_room) //loop to forward links to find the room to remove flow
		list = list->next;
	list->flow = UNUSED_FORWARD;
}

void	delete_residual_edge(t_edge *edge)
{
	unset_flow(edge->from->forward_list, edge->to);
	edge->to->prev = 0;
}

int	augment(t_edge *rev_edge, int rev_count)
{
	t_room	*room;
	t_edge	*temp;
	int		backward_edge_used;
	int		i;

	i = 0;
	backward_edge_used = 1;
	while (i < rev_count)
	{
		if (rev_edge[i].flow == BACKWARD)
		{
			delete_residual_edge(&rev_edge[i]);
			backward_edge_used = 0;
		}
		else
		{
			temp = rev_edge[i].to->forward_list;
			while (temp) // to set the forward edge flow to 1 //find a better way to do this instead of looping through all the forward links (hash map?)
			{
				if (temp->to == rev_edge[i].from)
					temp->flow = USED_FORWARD; //this one is the edge to the new found room
				temp = temp->next;
			}
			room = rev_edge[i].from;
			if (!room->prev)
				room->prev = rev_edge[i].to;
		}
		// printf("%s - ", rev_edge[i].from->name);
		i++;
	}
	// printf("%s\n", rev_edge[i - 1].to->name);
	return (backward_edge_used);
}

int conclude_path(t_edge **queue, int *tracer, int q_idx)
{
	t_edge	rev_edge[MAGIC_NUMBER];
	int fail = 0;
	int revq_idx;
	int	tar;

	revq_idx = 0;
	printf("%s - ", queue[q_idx]->to->name);
	edge_assign(&rev_edge[revq_idx++], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
	tar = tracer[q_idx];
	while (q_idx > 0)
	{
		// printf("%d <- %d\n", q_idx, tracer[q_idx]);
		if (q_idx == tar)
		{
			printf("%s - ", queue[q_idx]->to->name);
			if (queue[q_idx]->to->prev && queue[q_idx]->to->prev == queue[q_idx]->from) // if there is a backward edge that matches this rev_edge ->fail
			{
				fail = 1;
				break;
			}
			edge_assign(&rev_edge[revq_idx++], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
			tar = tracer[q_idx];
		}
		q_idx--;
	}
	printf("%s\n", queue[q_idx]->from->name);
	if (fail == 1)
	{
		printf("failed\n");
		return (0);
	}
	printf("path found Uwu\n");
	augment(rev_edge, revq_idx);
	return (1);
}
