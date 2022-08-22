/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ford_fulkerson.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:47:10 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/21 23:01:34 by qnguyen          ###   ########.fr       */
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
		retrace(&path[counted_path[i]], path[counted_path[i]].steps - 1);
		i++;
	}
}

static int	assign_max_flow_path(int *max_flow_path, int *counted_path, int flow)
{
	ft_memcpy(max_flow_path, counted_path, flow * sizeof(int));
	max_flow_path[flow] = -1;
	return (flow);
}

int *max_flow_path(t_path *path, int last_path)
{
	int	base_path;
	int	loop_path;
	int	i;
	int	max_flow;
	int	flow;
	int	*max_flow_path;
	int counted_path[last_path];

	base_path = 0;
	max_flow = 0;
	max_flow_path = ft_memalloc(sizeof(int) * last_path);
	while (base_path < last_path)
	{
		flow = 0;
		loop_path = base_path;
		while (loop_path < last_path)
		{
			i = 1;
			while (i < path[loop_path].steps - 1)
			{
				if (path[loop_path].room[i]->state == OCCUPIED_ROOM)
					break;
				path[loop_path].room[i]->state = OCCUPIED_ROOM;
				i++;
			}
			if (i == path[loop_path].steps - 1)
				counted_path[flow++] = loop_path;
 			else
				retrace(&path[loop_path], i);
			loop_path++;
		}
		if (flow > max_flow)
			max_flow = assign_max_flow_path(max_flow_path, counted_path, flow);
		retrace_all_path(path, counted_path, flow);
		base_path++;
	}
	return (max_flow_path);
}
