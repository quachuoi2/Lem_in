/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:56:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/21 23:11:20 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	set_route_steps(t_path *path)
{
	int	i;
	int	j;

	i = 0;
	while (path[i].room[0])
	{
		j = 0;
		while (path[i].room[j])
			j++;
		path[i].steps = j;
		i++;
	}
}

void	lemme_in(t_room *room)
{
	int		path_idx;
	int		room_idx;
	t_path	*path;

	path = malloc(sizeof(t_path) * NUM_OF_PATH);
	path_idx = 0;
	while (path_idx < NUM_OF_PATH)
		path[path_idx++].room = ft_memalloc(sizeof(t_room *) * NUM_OF_ROOM_PER_PATH);
	path_idx = 0;
	room_idx = 0;
	traceroute(path, room, &path_idx, &room_idx);
	set_route_steps(path);
	path_quicksort(path, 0, path_idx - 1);
	print_path(path, path_idx);
	max_flow_path(path, path_idx);
}

void	traceroute(t_path *path, t_room *room, int *path_idx, int *room_idx)
{
	t_rlist *temp = room->links;

	if (room->state == END_ROOM)
	{
		path[*path_idx].room[*room_idx] = room;
		conclude_path(path, path_idx, *room_idx);
		return;
	}
	room->crossed = 1;
	while (temp)
	{
		if (temp->room->crossed == 0)
		{
			path[*path_idx].room[*room_idx] = room;
			(*room_idx)++;
			traceroute(path, temp->room, path_idx, room_idx);
			(*room_idx)--;
		}
		temp = temp->next;
	}
	room->crossed = 0;
}

void	conclude_path(t_path *path, int *path_idx, int room_idx)
{
	int j;

	j = 0;
	while (j < room_idx)
	{
		if (path[*path_idx].room[j] == 0)
			path[*path_idx].room[j] = path[*path_idx - 1].room[j];
		printf("%s - ", path[*path_idx].room[j]->name);
		j++;
	}
	printf("%s\n", path[*path_idx].room[j]->name);
	(*path_idx)++;

/* 	if (*path_idx % NUM_OF_PATH == 0)
		path_expansion_jutsu(path, NUM_OF_PATH * ((*path_idx / NUM_OF_PATH) + 1)); */
}

/* void	path_expansion_jutsu(t_path *path, int path_amt)
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
