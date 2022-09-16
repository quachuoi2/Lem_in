/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:05:33 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/16 15:24:05 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_data(int *ants_num, int fd, t_rlist **list)
{
	char	*line;

	get_next_line(fd, &line);
	check_ants(line);
	*ants_num = ft_atoi(line);
	free(line);
	get_rooms(list, fd);
}

void	assign_room(t_room **room, char *line)
{
	char	**split;

	*room = (t_room *)malloc(sizeof(t_room));
	split = ft_strsplit(line, ' ');
	(*room)->name = ft_strdup(split[0]);
	(*room)->coord_x = ft_atoi(split[1]);
	(*room)->coord_y = ft_atoi(split[2]);
	//(*room)->ant = 0;
	(*room)->state = VACANT_ROOM;
	(*room)->occupied = 0;
	(*room)->path_idx = -1;
	(*room)->forward = 0;
	(*room)->backward = 0;
	(*room)->links = NULL;
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
	assign_room(room, *line);
	(*room)->state = start_end_state;
}

void	get_rooms(t_rlist **list, int fd)
{
	char	*line;
	t_room	*room;
	t_rlist	*temp;

	while (get_next_line(fd, &line))
	{
		room = NULL;
		if (line[0] != '#')
		{
			if (ft_strchr(line, '-'))
				break;
			assign_room(&room, line);
		}
		else if (!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end"))
			assign_start_end_room(&room, &line, fd);
		if (room)
			add_room_list(room, list);
		free(line);
	}
	while (*line) //also must stop when nonsense is entered
	{
		if (*line != '#')
			get_links(*list, line, fd);
		free(line);
		if (get_next_line(fd, &line) == DONE_READ)
			break;
	}
}

void	check_link(t_room *a, t_room *b)
{
	t_rlist	*temp;

	temp = a->links;
	while (temp)
	{
		if (!ft_strcmp(a->links->room->name, b->name))
			break;
		temp = temp->next;
	}
	add_room_list(a, &(b->links));
	add_room_list(b, &(a->links));
}

void	get_links(t_rlist *list, char *line, int fd)
{
	char	**split;
	t_room	*r1;
	t_room	*r2;

	if (line[0] != '#')
	{
		split = ft_strsplit(line, '-');
		r1 = NULL;
		r2 = NULL;
		while (list)
		{
			if (r1 && r2)
				break;
			if (!ft_strcmp(split[0], list->room->name))
				r1 = list->room;
			else if (!ft_strcmp(split[1], list->room->name))
				r2 = list->room;
			list = list->next;
		}
		check_link(r1, r2);
	}
	ft_arrdel(&split);
}
