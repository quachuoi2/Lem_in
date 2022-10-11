/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:47:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 16:12:50 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	assign_start_end_room(t_room *room, int room_state)
{
	check_duplicate_start_end(room, room_state);
	if (room_state == START_ROOM)
		g_source = room;
	else if (room_state == END_ROOM)
		g_sink = room;
}

int	assign_ants(char *line)
{
	int	i;

	if (g_ant != 0)
		return (0);
	i = 0;
	while (line[i] != 0)
		check_ants_char(line[i++]);
	g_ant = ft_atoi(line);
	check_ant_amount();
	return (1);
}

void	assign_room(char *line, int room_state)
{
	int		hash_result;
	char	**split;
	t_room	*room;

	room = (t_room *)malloc(sizeof(t_room));
	check_malloc(room);
	assign_start_end_room(room, room_state);
	room->steps = 0;
	room->ant = 0;
	room->prev = NULL;
	room->next = NULL;
	room->edge = NULL;
	split = ft_strsplit(line, ' ');
	room->name = ft_strdup(split[0]);
	hash_result = hash_room(room);
	check_valid_room(split, room, line, hash_result);
	room->coord_x = ft_atoi(split[1]);
	room->coord_y = ft_atoi(split[2]);
	ft_arrdel(&split);
}

void	assign_edge(char *line)
{
	char	**split;
	t_room	*r1;
	t_room	*r2;

	split = ft_strsplit(line, '-');
	r1 = retrieve_room(split[0]);
	r2 = retrieve_room(split[1]);
	check_valid_link(r1, r2, split, line);
	add_elist(r1, r2);
	add_elist(r2, r1);
	ft_arrdel(&split);
}
