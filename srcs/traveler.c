/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traveler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 07:28:05 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/05 09:02:16 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	move_to_next(t_room *room, t_room *next)
{
	if (room->ant != 0)
	{
		printf("L%d-%s ", room->ant, next->name);
		if (next->state != END_ROOM)
			next->ant = room->ant;
		else
			next->ant++;
		room->ant = 0;
	}
}

static void	first_little_step(t_room *room, t_path *cur_path, int *cur_ant)
{
	room->ant = *cur_ant;
	(*cur_ant)++;
	cur_path->ant_count--;
	printf("L%d-%s ", room->ant, room->name);
}

void	exotic_ant_travelers()
{
	int		path_idx;
	int		room_idx;
	int		cur_ant;
	t_room **room;

	cur_ant = 1;
	while (best_paths[0]->huone[best_paths[0]->steps - 1]->ant < g_ant) // while endroom's ant is less than the total ants (ants havent fully moved to endroom)
	{
		path_idx = 0;
		while (path_idx < best_p_count)
		{
			room = best_paths[path_idx]->huone;
			room_idx = best_paths[path_idx]->steps - 1;
			while (--room_idx >= 0)
				move_to_next(room[room_idx], room[room_idx + 1]);
			if (cur_ant <= g_ant && best_paths[path_idx]->ant_count > 0)
				first_little_step(room[0], best_paths[path_idx], &cur_ant);
			path_idx++;
		}
		printf("\n");
	}
}
