/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:39 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/22 19:36:20 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int bfs(t_edge *start, int ant)
{
 	int q_rem = 1;
	int q_count = 1;
	int q_idx = 0;
	int	path_found = 0;
	t_edge *queue[MAGIC_NUMBER];
	int tracer[MAGIC_NUMBER];
	t_path_group cur;

	// init_path_groups(&cur);
	queue[0] = start;
	while (q_rem--)
	{
		if (queue[q_idx]->crossed != CROSSED)
		{
			// printf("NV %d: %s - %s\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name);
			if (queue[q_idx]->to->state != END_ROOM /* && queue[q_idx]->to->up_for_grabz == 0 */) //one change here as well
			{
				if (queue[q_idx]->to->forward_list == NULL)
					q_rem += search_free_link(queue, &q_count, q_idx, tracer);
				else
					q_rem += search_forward(queue, &q_count, q_idx, tracer);
			}
			else
			{
				if (conclude_path(queue, tracer, q_idx)  == 1)
				{
					// adjust_path_group(&cur, path, &path_idx);
					// line_count(&cur, path, ant);
					// if (best.line_count > cur.line_count || best.line_count == 0)
					// 	assign_best_group(&best, &cur);
					// printf("LC: %d\n", best.line_count);
					path_found = 1;
				}
			}
			queue[q_idx]->crossed = CROSSED;
		}
		// else
			// printf("AV %d: %s - %s\n", q_idx, queue[q_idx]->from->name, queue[q_idx]->to->name);
		q_idx++;
	}
	CROSSED++;
	return (path_found);
}
