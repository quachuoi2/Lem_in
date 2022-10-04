/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 17:47:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/04 11:34:09 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	assign_room(t_room **room, char *line, int room_state)
{
	char	**split;

	*room = (t_room *)malloc(sizeof(t_room));
	split = ft_strsplit(line, ' ');
	check_invalid_room_input(split);
	(*room)->name = ft_strdup(split[0]);
	(*room)->coord_x = ft_atoi(split[1]);
	(*room)->coord_y = ft_atoi(split[2]);
	(*room)->state = room_state;
	(*room)->step_count = 0;
	(*room)->ant = 0;
	(*room)->prev = NULL;
	(*room)->next = NULL;
	(*room)->edge = NULL;
	check_duplicate_room(hash_room(*room));
	ft_arrdel(&split);
}

void	assign_start_end_room(t_room **room, char **line, int fd)
{
	int	start_end_state;

	if ((*line)[2] == 's')
		start_end_state = START_ROOM;
	else
		start_end_state = END_ROOM;
	free(*line);
	get_next_line(fd, line);
	assign_room(room, *line, start_end_state);
	(*room)->state = start_end_state;
}

void	assign_edge(t_room *a, t_room *b)
{
	t_edge	*temp;

	temp = a->edge;
	while (temp) //check for existing duplicate room //skipping this saves a lot of time
	{
		if (!ft_strcmp(a->edge->to->name, b->name))
			return;
		temp = temp->next;
	}
	add_elist(a, b);
	add_elist(b, a);
}
