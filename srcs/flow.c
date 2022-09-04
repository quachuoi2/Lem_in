/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:47:10 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/04 02:50:42 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	target_flow_count(t_path *path, int *best_group, int max_ant)
{
	int	path_idx;
	int	line;
	int	step;

	path_idx = 0;
	step = 0;
	line = path[best_group[path_idx]].steps;
	while (max_ant)
	{
		while (best_group[path_idx + 1] != -1 && line >= path[best_group[path_idx + 1]].steps && step == 0)
			path_idx++;
		path[best_group[step]].ant_count++;
		step++;
		if (step > path_idx) //every path gets +1 ant before +1 line //step == path_idx + 1
		{
			line++;
			step = 0;
		}
		max_ant--;
	}
	//print_path_ant_count(path, best_group);
	return (path_idx + 1); //+1 because returning flow amount, not index
}

static int	compare_max(t_path *path, int *tar_group, int *new_group, int flow, int max_flow)
{
	int			i;
	int			new_room_count;
	static int	max_room_count;

	new_room_count = path_room_count(path, new_group, flow);
	if (flow > max_flow
		|| (flow == max_flow && (new_room_count < max_room_count || max_room_count == 0)))
	{
		assign_path(tar_group, new_group, flow);
		max_room_count = new_room_count;
	}
	return (flow);
}

// printf("tp: %d %d = %d\n", tar_group[0], tar_group[1], max_room_count);
// printf("%d %d = %d\n", tar_group[0], tar_group[1], tar_room_count);
// printf("%d %d = %d\n\n", new_group[0], new_group[1], new_room_count);
static int	compare_target_group(int *tar_group, int *new_group, int flow, int room_count)
{
	static int	tar_room_count;

	if (room_count < tar_room_count || tar_room_count == 0)
	{
		assign_path(tar_group, new_group, flow);
		tar_room_count = room_count;
		return (1);
	}
	return (0);
}

static int	calculate_flow(t_path *path, int path_idx, int target_flow, int *temp_group, int *target_group, int iter)
{
	int flow;
	int	room_count;
	static int threshhold;

	flow = 0;
	room_count = 0;

	while (path[path_idx].room[0])
	{
		if (check_path(path, path_idx))
		{
			temp_group[flow++] = path_idx;
			temp_group[flow] = -1;
			room_count += path[path_idx].steps;
		}
		if (flow == target_flow)
		{
			if (iter == 2 && (room_count < threshhold || threshhold == 0))
			{
				retrace_all_path(path, temp_group, flow);
				room_count = do_the_thingy(path, temp_group, flow);
			}
			if (compare_target_group(target_group, temp_group, flow, room_count) && iter == 2)
				threshhold = room_count * 1.2;
			break; //test feature for optimization
		}
		path_idx++;
	}
	return (flow);
}

void	max_flow_path(t_path *path, int *max_flow_group, int target_flow, int iter)
{
	int	base_path;
	int	max_flow;
	int	flow;
	int temp_group[g_final_idx];
	int target_group[g_final_idx];

	base_path = 0;
	max_flow = 0;
	target_group[0] = -1;
	while (base_path < g_final_idx)
	{
		flow = calculate_flow(path, base_path, target_flow, temp_group, target_group, iter);
		retrace_all_path(path, temp_group, flow);
		if (flow >= max_flow && flow < target_flow) //test feature for optimization
			max_flow = compare_max(path, max_flow_group, temp_group, flow, max_flow);
		base_path++;
	}
	if (target_group[0] != -1)
		assign_path(max_flow_group, target_group, target_flow);
	//print_flow_path(path, max_flow_group, 1);
}
