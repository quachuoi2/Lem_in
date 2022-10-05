/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/05 10:50:58 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_conclude(t_edge *rev_edge, int revq_idx)
{
	int i = revq_idx;
	printf("conclude: ");
	while (revq_idx--)
	{
		printf("%5s - ", rev_edge[revq_idx].to->name);
	}
	printf("%5s\n", rev_edge[revq_idx + 1].from->name);
	printf("%8s: ", "flow");
	while (i--)
	{
		printf("%5d - ", rev_edge[i].flow);
	}
	printf("\n");
}

void	check_backward_usage(int *current_status, int flow)
{
	if (flow == BACKWARD)
		*current_status = BACKWARD;
}

int		check_lesser_step_path(int old_amount, int new_amount, t_room **old_long_room, t_room *current_room)
{
	if (new_amount > old_amount)
		return (0);
	*old_long_room = current_room;
	return (1);
}

static int conclude_path(t_edge **que, t_tracer *tracer, int q_i)
{
	t_edge	rev_edge[q_i];
	int		rev_i;
	int		target_idx;
	int		backward_edge_used;
	t_room	*old_long_room;

	rev_i = 0;
	old_long_room = 0;
	backward_edge_used = 0;
	set_edge(&rev_edge[rev_i++], que[q_i]->to, que[q_i]->from, que[q_i]->flow);
	target_idx = tracer[q_i].idx;
	while (q_i > 0)
	{
		// printf("%d <- %d\n", q_i, tracer[q_i].idx);
		if (q_i == target_idx)
		{
			if (que[q_i]->to->prev == que[q_i]->from && // if there is a backward edge that matches this rev_edge ->fail
				check_lesser_step_path(que[q_i]->to->step_count, que[q_i]->to->step_count, &old_long_room, que[q_i]->from) == 0)
					return (0);
			set_edge(&rev_edge[rev_i], que[q_i]->to, que[q_i]->from, que[q_i]->flow);
			check_backward_usage(&backward_edge_used, rev_edge[rev_i++].flow);
			target_idx = tracer[q_i].idx;
		}
		q_i--;
	}
	// print_conclude(rev_edge, rev_i);
	return (augment(rev_edge, rev_i, old_long_room, backward_edge_used));
}

int bfs(t_edge *start)
{
 	int			q_rem = 1;
	int			q_count = 1;
	int			q_idx = 0;
	int			path_found = 0;
	t_edge		*queue[MAGIC_NUMBER];
	t_tracer	tracer[MAGIC_NUMBER];

	queue[0] = start;
	tracer[0].step_count = 0;
	while (q_rem--)
	{
		if (queue[q_idx]->crossed != CROSSED)
		{
			// printf("NV %d: %s -> %s = %d\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name, tracer[q_idx].step_count);
			if (queue[q_idx]->to->state != END_ROOM)
				q_rem += search_forward(queue, &q_count, q_idx, tracer);
			else
			{
				path_found = conclude_path(queue, tracer, q_idx);
				if (path_found != 0)
					break;
			}
			queue[q_idx]->crossed = CROSSED;
		}
		// else
			// printf("AV %d: %s -> %s\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name);
		q_idx++;
	}
	CROSSED++;
	return (path_found);
}
