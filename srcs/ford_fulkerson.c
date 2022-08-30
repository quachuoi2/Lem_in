/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ford_fulkerson.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:47:10 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/30 18:42:18 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	retrace(t_path *cur_path, int reached_room)
{
	int	i;

	i = 1;
	while (i < reached_room)
		cur_path->room[i++]->state = VACANT_ROOM;
}

static void	retrace_all_path(t_path *path, int *counted_path, int flow)
{
	int	i;

	i = 0;
	while (i < flow)
	{
		retrace(&path[counted_path[i]], path[counted_path[i]].steps);
		i++;
	}
}

static int	assign_max_flow_path(int *max_flow_path, int *counted_path, int flow)
{
	ft_memcpy(max_flow_path, counted_path, flow * sizeof(int));
	max_flow_path[flow] = -1;
	return (flow);
}

int	flow_count(t_path *path, int *best_path, int max_ant)
{
	int	path_idx;
	int	line;
	int	step;

	path_idx = 0;
	step = 0;
	line = path[best_path[path_idx]].steps;
	while (max_ant)
	{
		if (best_path[path_idx + 1] != -1 && line >= path[best_path[path_idx + 1]].steps && step == 0)
			path_idx++;
		path[best_path[step]].ant_count++;
		step++;
		if (step > path_idx) //every path gets +1 ant before +1 line //step == path_idx + 1
		{
			line++;
			step = 0;
		}
		max_ant--;
	}
/* 	int i = 0;
	while (best_path[i] != -1)
		printf("%d ", best_path[i++]);
	printf("\n");
	i = 0;
	while (best_path[i] != -1)
		printf("%d ", path[best_path[i++]].ant_count);
	printf("\n"); */
	return (path_idx + 1); //+1 because returning flow amount, not index
}

void	max_flow_path(t_path *path, int last_path, int *max_flow_path, int target_flow)
{
	int	base_path;
	int	loop_path;
	int	i;
	int	max_flow;
	int	flow;
	int counted_path[last_path];

	base_path = 0;
	max_flow = 0;
	while (base_path < last_path)
	{
		flow = 0;
		loop_path = base_path;
		while (loop_path < last_path)
		{
			i = 1;
			while (i < path[loop_path].steps)
			{
				if (path[loop_path].room[i]->state == OCCUPIED_ROOM)
					break;
				path[loop_path].room[i]->state = OCCUPIED_ROOM;
				i++;
			}
			if (i == path[loop_path].steps)
				counted_path[flow++] = loop_path;
 			else
				retrace(&path[loop_path], i);
			if (flow == target_flow)
			{
				assign_max_flow_path(max_flow_path, counted_path, flow);
				break;
			}
			loop_path++;
		}
		retrace_all_path(path, counted_path, flow);
		if (flow == target_flow)
			break;
		else if (flow > max_flow)
			max_flow = assign_max_flow_path(max_flow_path, counted_path, flow);
		base_path++;
	}
}
