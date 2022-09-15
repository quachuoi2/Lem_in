/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:07:03 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/14 11:19:49 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	conclude_path(t_path *path, int room_idx)
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

void	dfs(t_path *path, t_room *room, int *room_idx)
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
			dfs(path, temp->room, room_idx);
			(*room_idx)--;
		}
		temp = temp->next;
	}
	room->crossed = 0;
}