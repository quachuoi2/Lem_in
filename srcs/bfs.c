/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/25 18:28:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	backward_augment(t_edge *rev_edge, int rev_count)
{
	int		i;
	int		step_count;

	i = rev_count;
	step_count = 1;
	printf("augment: \n");
	while (i > -1)
	{
		printf("%s - ", rev_edge[i].to->name);
		if (rev_edge[i].flow == BACKWARD)
		{
			delete_residual(rev_edge[i].from);
			if (rev_edge[i - 1].flow == BACKWARD)
				rev_edge[i].from->step_count = 0;
		}
		else
		{
			set_flow(rev_edge[i].to->forward_list, rev_edge[i].from, USED_FORWARD);
			rev_edge[i].from->prev = rev_edge[i].to;
			rev_edge[i].to->next = rev_edge[i].from;
			if (i < rev_count && rev_edge[i + 1].flow == BACKWARD) // if i = rev_count -> uninitialized
				step_count = rev_edge[i].to->step_count + 1;
			rev_edge[i].from->step_count = step_count++;
			if (rev_edge[i - 1].flow == BACKWARD)
				update_step_count(rev_edge[i].from->next);
		}
		i--;
	}
	printf("%s\n", rev_edge[i + 1].from->name);
	return (42);
}

static int	pure_forward_augment(t_edge *rev_edge, int rev_count)
{
	int		i;
	int		step_count;

	i = rev_count;
	step_count = 1;
	printf("augment: ");
	while (i > -1)
	{
		printf("%s - ", rev_edge[i].to->name);
		set_flow(rev_edge[i].to->forward_list, rev_edge[i].from, USED_FORWARD);
		rev_edge[i].from->prev = rev_edge[i].to;
		rev_edge[i].to->next = rev_edge[i].from;
		rev_edge[i].from->step_count = step_count++;
		i--;
	}
	printf("%s\n", rev_edge[i + 1].from->name);
	return (42);
}

static int conclude_path(t_edge **queue, t_counter *tracer, int q_idx)
{
	t_edge	rev_edge[MAGIC_NUMBER];
	int fail = 0;
	int revq_idx;
	int	tar;
	int		backward_edge_used;
	t_room	*old_long_path_room = 0;

	revq_idx = 0;
	backward_edge_used = 0;
	// printf("%s - %d\n", queue[q_idx]->to->name, tracer[q_idx].step_count);
	edge_assign(&rev_edge[revq_idx], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
	// printf("conclude: %s - ", queue[q_idx]->to->name);
	revq_idx++;
	tar = tracer[q_idx].idx;
	while (q_idx > 0)
	{
		// printf("%d <- %d\n", q_idx, tracer[q_idx].idx);
		if (q_idx == tar)
		{
			if (queue[q_idx]->to->prev == queue[q_idx]->from) // if there is a backward edge that matches this rev_edge ->fail
			{
				if (queue[q_idx]->to->step_count <= tracer[q_idx].step_count)
				{
					fail = 1;
					break;
				}
				old_long_path_room = queue[q_idx]->from;
			}
			edge_assign(&rev_edge[revq_idx], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
			if (rev_edge[revq_idx].flow == BACKWARD)
				backward_edge_used = BACKWARD;
			revq_idx++;
			// printf("%s - %d\n", queue[q_idx]->to->name, tracer[q_idx].step_count);
			// printf("%s - ", queue[q_idx]->to->name);
			tar = tracer[q_idx].idx;
		}
		q_idx--;
	}
	// printf("%s\n", queue[q_idx]->from->name);
	if (fail == 1)
		return (0);
	if (old_long_path_room != 0)
		remove_old_longer_path(old_long_path_room);
	if (backward_edge_used == BACKWARD)
		backward_augment(rev_edge, revq_idx - 1);
	else
		pure_forward_augment(rev_edge, revq_idx - 1);
	return (1);
}

int bfs(t_edge *start, int ant)
{
 	int q_rem = 1;
	int q_count = 1;
	int q_idx = 0;
	int	path_found = 0;
	t_edge *queue[MAGIC_NUMBER];
	t_counter tracer[MAGIC_NUMBER];

	// init_path_groups(&cur);
	queue[0] = start;
	tracer[0].step_count = 0;
	while (q_rem--)
	{
		if (queue[q_idx]->crossed != CROSSED)
		{
			// printf("NV %d: %s -> %s = %d\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name, tracer[q_idx].step_count);
			if (queue[q_idx]->to->state != END_ROOM)
			{
				if (queue[q_idx]->to->forward_list == NULL)
					q_rem += search_free_link(queue, &q_count, q_idx, tracer);
				else
					q_rem += search_forward(queue, &q_count, q_idx, tracer);
			}
			else if (conclude_path(queue, tracer, q_idx) == 1)
				path_found = 1;
			queue[q_idx]->crossed = CROSSED;
		}
		// else
			// printf("AV %d: %s -> %s\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name);
		q_idx++;
	}
	CROSSED++;
	return (path_found);
}
