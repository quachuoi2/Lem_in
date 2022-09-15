/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:26:07 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/15 20:18:35 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_path_groups(t_path_group *group)
{
	group->tol_step = 0;
	group->path_count = 0;
	group->line_count = 0;
	group->group = ft_memalloc(sizeof(int) * MAGIC_NUMBER);
}

void	assign_edge_to_room(t_room *room, t_edge *edge)
{
	room->edge = edge;
}

void	adjust_path_group(t_path_group *cur, t_path *path, int *path_idx)
{
	cur->group[cur->path_count] = *path_idx;
	cur->tol_step += path[*path_idx].steps;
	cur->path_count++;
	(*path_idx)++;
}

void	assign_path_group(t_path_group *best, t_path_group *cur)
{
	int	i;

	best->line_count = cur->line_count;
	best->path_count = cur->path_count;
	best->tol_step = cur->tol_step;
	i = 0;
	while (i < best->path_count)
	{
		best->group[i] = cur->group[i];
		i++;
	}
}

/* void	retrace_rooms(t_path *cur_path, int reached_room)
{
	int	i;

	i = 1;
	while (i < reached_room)
		cur_path->room[i++]->state = VACANT_ROOM;
}

void	retrace_all_path(t_path *path, int *temp_path, int flow)
{
	int	i;

	i = 0;
	while (i < flow)
	{
		retrace_rooms(&path[temp_path[i]], path[temp_path[i]].steps);
		path[temp_path[i]].ant_count = 0;
		i++;
	}
}

void	assign_path(int *dest_path, int *src_path, int flow)
{
	ft_memcpy(dest_path, src_path, flow * sizeof(int));
	dest_path[flow] = -1;
}

int	path_room_count(t_path *path, int *path_idx, int flow)
{
	int	i;
	int	room_count;

	i = 0;
	room_count = 0;
	while (i < flow)
		room_count += path[path_idx[i++]].steps;
	return (room_count);
}

int	check_path(t_path *path, int path_idx)
{
	int i = 1;

	while (i < path[path_idx].steps && path[path_idx].room[i]->state != OCCUPIED_ROOM)
		path[path_idx].room[i++]->state = OCCUPIED_ROOM;
	if (i == path[path_idx].steps)
		return (1);
	retrace_rooms(&path[path_idx], i);
	return (0);
}

void	path_expansion_jutsu(t_path *path, int path_amt)
{
	int	i;
	int	j;
	char **temp_rooms;

	i = 0;
	while (path[i].room[0])
	{
		temp_rooms = ft_memalloc(sizeof(char *) * NUM_OF_ROOM_PER_PATH);
		j = 0;
		while (path[i].room[j])
		{
			temp_rooms[j] = ft_strdup(path[i].room[j]);
			free(path[i].room[j]);
			path[i].room[j] = temp_rooms[i];
			j++;
		}
		free(path[i].room);
		path[i].room = temp_rooms;
		i++;
	}
} */