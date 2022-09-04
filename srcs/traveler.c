/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traveler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:41:12 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/02 01:20:58 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	instant_finish(t_path *path, int max_ant)
{
	int	i = 0;

	if (path[0].room[1]->state == END_ROOM)
	{
		while (i <= max_ant)
			printf("L%d-%s ", i++, path[0].room[1]->name);
		printf("\n");
		return (1);
	}
	return (0);
}

int	exotic_ant_traveler(t_path *path, int *best_path, int ant_num, int target_flow)
{
	int	path_idx;
	int	r_idx;
	int	cur_ant;
	t_room **room;

	cur_ant = 1;
	while (path[0].room[path[0].steps]->ant < ant_num)
	{
		path_idx = 0;
		while (path_idx < target_flow)
		{
			room = path[best_path[path_idx]].room;
			r_idx = path[best_path[path_idx]].steps - 1;
			while (r_idx > 0)
			{
				if (room[r_idx]->ant != 0)
				{
					printf("L%d-%s ", room[r_idx]->ant, room[r_idx + 1]->name);
					if (room[r_idx + 1]->state != END_ROOM)
						room[r_idx + 1]->ant = room[r_idx]->ant;
					else
						room[r_idx + 1]->ant++;
					room[r_idx]->ant = 0;
				}
				r_idx--;
			}
			if (cur_ant <= ant_num && path[best_path[path_idx]].ant_count > 0)
			{
				room[1]->ant = cur_ant;
				path[best_path[path_idx]].ant_count--;
				printf("L%d-%s ", room[1]->ant, room[1]->name);
				cur_ant++;
			}
			path_idx++;
		}
		printf("\n");
	}
}
