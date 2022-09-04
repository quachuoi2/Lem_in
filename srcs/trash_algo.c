/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_algo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 03:03:25 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/04 02:49:35 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	occupy_rooms(t_path *path, int *best_group, int flow)
{
	int	i = 0;
	while (i < flow)
	{
		int j = 1;
		while (j < path[best_group[i]].steps)
			path[best_group[i]].room[j++]->state = OCCUPIED_ROOM;
		i++;
	}
}

static int	temp_comp(t_path *path, int *tar_group, int *new_group, int flow)
{
	int	tar_room_count = path_room_count(path, tar_group, flow);
	int new_room_count = path_room_count(path, new_group, flow);
	if (new_room_count < tar_room_count)
	{
		assign_path(tar_group, new_group, flow);
		tar_room_count = new_room_count;
		return (1);
	}
	return (0);
}

void		recurs(t_path *path, int *ctg, int *btg, int ctg_idx, int target_flow)
{
	int temp_path_idx;

	if (ctg_idx < target_flow - 1)
	{
		temp_path_idx = ctg[ctg_idx + 1];
		ctg[ctg_idx] = ctg[ctg_idx - 1] + 1;
		while (ctg[ctg_idx] <= ctg[ctg_idx + 1])
		{
			if (check_path(path, ctg[ctg_idx]))
			{
				recurs(path, ctg, btg, ctg_idx + 1, target_flow);
				ctg[ctg_idx + 1] = temp_path_idx;
				retrace_rooms(&path[ctg[ctg_idx]], path[ctg[ctg_idx]].steps);
			}
			ctg[ctg_idx]++;
		}
	}
	else
	{
		temp_path_idx = ctg[ctg_idx];
		ctg[ctg_idx] = ctg[ctg_idx - 1] + 1;
		while (!check_path(path, ctg[ctg_idx]) && ctg[ctg_idx] <= temp_path_idx)
			ctg[ctg_idx]++;
		if (ctg[ctg_idx] > temp_path_idx)
			return ;
		temp_comp(path, btg, ctg, target_flow);
		retrace_rooms(&path[ctg[ctg_idx]], path[ctg[ctg_idx]].steps);
	}
}

int	do_the_thingy(t_path *path, int *btg, int target_flow)
{
	int	ctg_idx = 1;
	int ctg[g_final_idx];

	assign_path(ctg, btg, target_flow);
	occupy_rooms(path, ctg, ctg_idx); //occupy only until before the current idx of temp_group
	recurs(path, ctg, btg, ctg_idx, target_flow);
	return (path_room_count(path, btg, target_flow));
}