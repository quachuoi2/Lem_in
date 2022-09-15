/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:56:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/15 18:39:10 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	line_count(t_path_group *cur, t_path *path, int max_ant)
{
	int	line;
	int	step;
	int	group_idx;

	step = 0;
	group_idx = 0;
	line = path[cur->group[group_idx]].steps;
	while (max_ant)
	{
		while (group_idx + 1 < cur->path_count && line >= path[cur->group[group_idx + 1]].steps && step == 0) //move through all the paths with the same amt of steps
			group_idx++;
		path[cur->group[step]].ant_count++; //every path gets +1 ant before +1 line
		step++; //every path gets +1 ant before +1 line
		if (step > group_idx)  //reset when each path got +1 ant //step == group_idx + 1
		{
			line++;
			step = 0;
		}
		max_ant--;
	}
	cur->line_count = line - 1;
	//return (group_idx + 1); //+1 because returning flow amount, not index
}

/* void	lemme_in(t_room *room, t_path *path, int ant_num)
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
} */
