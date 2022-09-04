/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:56:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/04 03:16:12 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	conclude_path(t_path *path, int room_idx)
{
	int j;

	j = 0;
	while (j < room_idx)
	{
		if (path[g_final_idx].room[j] == 0)
			path[g_final_idx].room[j] = path[g_final_idx - 1].room[j];
		j++;
	}
	path[g_final_idx].room[room_idx + 1] = 0;
	path[g_final_idx].steps = j;
	path[g_final_idx].ant_count = 0;
	(g_final_idx)++;
/* 	if (*g_final_idx % NUM_OF_PATH == 0)
		path_expansion_jutsu(path, NUM_OF_PATH * ((*g_final_idx / NUM_OF_PATH) + 1)); */
}

void	traceroute(t_path *path, t_room *room, int *room_idx)
{
	t_rlist *temp = room->links;

	if (room->state == END_ROOM)
	{
		path[g_final_idx].room[*room_idx] = room;
		conclude_path(path, *room_idx);
		return;
	}
	room->crossed = 1;
	while (temp)
	{
		if (temp->room->crossed == 0)
		{
			path[g_final_idx].room[*room_idx] = room;
			(*room_idx)++;
			traceroute(path, temp->room, room_idx);
			(*room_idx)--;
		}
		temp = temp->next;
	}
	room->crossed = 0;
}

void	lemme_in(t_room *room, t_path *path, int ant_num)
{
	int	room_idx;
	int	*best_path;

	g_final_idx = 0;
	room_idx = 0;
	traceroute(path, room, &room_idx);
	path_quicksort(path, 0, g_final_idx - 1);
	if (instant_finish(path, ant_num))
		return;
	initialize_best_path(&best_path);
	max_flow_path(path, best_path, target_flow_count(path, best_path, ant_num), 1);
	max_flow_path(path, best_path, target_flow_count(path, best_path, ant_num), 2);
	exotic_ant_traveler(path, best_path, ant_num, target_flow_count(path, best_path, ant_num));
	//free best path
}
