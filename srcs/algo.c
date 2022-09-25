/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:56:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/24 20:00:36 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* void	line_count(t_path_group *cur, t_path *path, int max_ant)
{
	int	path_idx;
	int	line;
	int	step;

	path_idx = 0;
	step = 0;
	line = path[best_group[path_idx]].steps;
	while (max_ant)
	{
		while (best_group[path_idx + 1] != -1 && line >= path[best_group[path_idx + 1]].steps && step == 0)  //move through all the paths with the same amt of steps
			path_idx++;
		path[best_group[step]].ant_count++;//every path gets +1 ant before +1 line
		step++; //every path gets +1 ant before +1 line
		if (step > path_idx)  //reset when each path got +1 ant //step == group_idx + 1
		{
			line++;
			step = 0;
		}
		max_ant--;
	}
	//print_path_ant_count(path, best_group);
	return (path_idx + 1); //+1 because returning flow amount, not index
} */