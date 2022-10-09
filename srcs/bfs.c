/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/09 16:06:48 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	check_backward_usage(int *current_status, int flow)
{
	if (flow == BACKWARD)
		*current_status = BACKWARD;
}

static int	lesser_step_path(t_edge *edge, int new_steps, t_room **old_room)
{
	int		old_steps;

	old_steps = edge->to->steps;
	if (new_steps >= old_steps)
		return (NOT_FOUND);
	*old_room = edge->from;
	return (FOUND);
}

static int	conclude_path(t_edge **que, t_tracer *tracer, int q_i)
{
	int		r_i;
	int		target_idx;
	int		backward_edge_used;
	t_edge	r_que[MAGIC_NUMBER];
	t_room	*old_long_room;

	init_conclude_path_data(&r_i, &backward_edge_used, &old_long_room);
	set_edge(&r_que[r_i++], que[q_i]->to, que[q_i]->from, que[q_i]->flow);
	target_idx = tracer[q_i].idx;
	while (q_i > 0)
	{
		if (q_i == target_idx)
		{
			if (que[q_i]->to->prev == que[q_i]->from
				&& lesser_step_path
				(que[q_i], tracer[q_i].steps, &old_long_room) == NOT_FOUND)
				return (NOT_FOUND);
			set_edge(&r_que[r_i], que[q_i]->to, que[q_i]->from, que[q_i]->flow);
			check_backward_usage(&backward_edge_used, r_que[r_i++].flow);
			target_idx = tracer[q_i].idx;
		}
		q_i--;
	}
	return (augment(r_que, r_i, old_long_room, backward_edge_used));
}

int	bfs(t_edge *start)
{
	t_queue		q;
	int			path_result;
	t_tracer	tracer[MAGIC_NUMBER];

	init_queue(&q, start);
	tracer[0].steps = 0;
	path_result = 0;
	while (q.remaining--)
	{
		if (q.queue[q.idx]->crossed != g_crossed)
		{
			if (q.queue[q.idx]->to != g_sink)
				q.remaining += search(q.queue, &q.count, q.idx, tracer);
			else
			{
				path_result = conclude_path(q.queue, tracer, q.idx);
				if (path_result != NOT_FOUND)
					break ;
			}
			q.queue[q.idx]->crossed = g_crossed;
		}
		q.idx++;
	}
	g_crossed++;
	return (path_result);
}
