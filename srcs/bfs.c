/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/01 09:47:14 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_conclude(t_edge *rev_edge, int revq_idx, int time)
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

static int conclude_path(t_edge **queue, t_tracer *tracer, int q_idx)
{
	t_edge	rev_edge[q_idx];
	int		revq_idx;
	int		tar;
	int		backward_edge_used;
	t_room	*old_long_path_room = 0;
	static int	time;

	time++;
	revq_idx = 0;
	backward_edge_used = 0;
	set_edge(&rev_edge[revq_idx++], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
	tar = tracer[q_idx].idx;
	while (q_idx > 0)
	{
		// printf("%d <- %d\n", q_idx, tracer[q_idx].idx);
		if (q_idx == tar)
		{
			if (queue[q_idx]->to->prev == queue[q_idx]->from) // if there is a backward edge that matches this rev_edge ->fail
			{
				if (queue[q_idx]->to->step_count <= tracer[q_idx].step_count)
					return (0);
				old_long_path_room = queue[q_idx]->from;
			}
			set_edge(&rev_edge[revq_idx], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
			if (rev_edge[revq_idx++].flow == BACKWARD)
				backward_edge_used = BACKWARD;
			tar = tracer[q_idx].idx;
		}
		q_idx--;
	}
	// print_conclude(rev_edge, revq_idx, time);
	if (old_long_path_room != 0)
		remove_old_longer_path(old_long_path_room); //and reconnect new room instead of pure_forward_augment
	if (backward_edge_used == BACKWARD)
		mixed_augment(rev_edge, revq_idx - 1);
	else
		pure_forward_augment(rev_edge, revq_idx - 1);
	return (1);
}

int bfs(t_edge *start)
{
 	int			q_rem = 1;
	int			q_count = 1;
	int			q_idx = 0;
	int			path_found = 0;
	t_edge		**queue;
	t_tracer	*tracer;

	queue = ft_memalloc(sizeof(t_edge *) * MAGIC_NUMBER);
	tracer = ft_memalloc(sizeof(t_tracer) * MAGIC_NUMBER);
	queue[0] = start;
	tracer[0].step_count = 0;
	while (q_rem--)
	{
		if (queue[q_idx]->crossed != CROSSED)
		{
			// printf("NV %d: %s -> %s = %d\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name, tracer[q_idx].step_count);
			if (queue[q_idx]->to->state != END_ROOM)
				q_rem += search_forward(queue, &q_count, q_idx, tracer);
			else if (conclude_path(queue, tracer, q_idx) == 1)
			{
				path_found = 1;
				break;
			}
			queue[q_idx]->crossed = CROSSED;
		}
		// else
			// printf("AV %d: %s -> %s\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name);
		q_idx++;
	}
	CROSSED++;
	ft_memdel((void **)&queue);
	ft_memdel((void **)&tracer);
	return (path_found);
}
