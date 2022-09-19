/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/18 21:50:22 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


void bfs(t_edge *start, int ant)
{
 	int q_rem = 1;
	int q_count = 1;
	int q_idx = 0;
	int revq_idx = 0;
	int path_idx = 0;
	t_edge *queue[MAGIC_NUMBER];
	t_edge rev_queue[MAGIC_NUMBER];
	t_path path[MAGIC_NUMBER];
	t_path_group cur;

	init_path_groups(&best);
	init_path_groups(&cur);

	queue[0] = start;
	while (q_rem--)
	{
		printf("%s - %s\n", queue[q_idx]->from->name, queue[q_idx]->to->name);
		if (queue[q_idx]->to->state != END_ROOM)
		{
			if (queue[q_idx]->to->visited != VISITED)
			{
				edge_assign(&rev_queue[revq_idx], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
				revq_idx++;
				if (queue[q_idx]->to->occupied == UNOCCUPIED) //change all to dispatch table?
				{
					if (queue[q_idx]->to->forward_list == NULL)
						q_rem += search_free_link(queue, &q_count, q_idx, UNVISITED);
					else
						q_rem += search_forward(queue, &q_count, q_idx);
				}
				else
					q_rem += search_backward(queue, &q_count, q_idx);
				queue[q_idx]->to->visited = VISITED;
			}
		}
		else
		{
			edge_assign(&rev_queue[revq_idx], queue[q_idx]->to, queue[q_idx]->from, queue[q_idx]->flow);
			if (conclude_path(rev_queue, revq_idx, path, path_idx) == 1)
			{
				printf("path found UwU\n\n");
				// adjust_path_group(&cur, path, &path_idx);
				// line_count(&cur, path, ant);
				// if (best.line_count > cur.line_count || best.line_count == 0)
				// 	assign_best_group(&best, &cur);
				// printf("LC: %d\n", best.line_count);
			}
		}
		q_idx++;
	}
	printf("\n");
	VISITED++;
}
