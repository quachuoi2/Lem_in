/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:05:33 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/08 02:48:56 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_ants(int *ants_num)
{
	char	*line;

	get_next_line(0, &line);
	*ants_num = ft_atoi(line);
	//check if number is valid
	free(line);
}

void	assign_room(t_room **room, char *line)
{
	char	**split;

	*room = (t_room *)malloc(sizeof(t_room));
	split = ft_strsplit(line, ' ');
	(*room)->name = ft_strdup(split[0]);
	(*room)->coord_x = ft_atoi(split[1]);
	(*room)->coord_y = ft_atoi(split[2]);
	(*room)->state = 0;
	(*room)->links = NULL;
	ft_arrdel(&split);
}

void	assign_start_end_room(t_room **room, char **line)
{
	int	start_end_state;

	if ((*line)[2] == 's')
		start_end_state = -1;
	else
		start_end_state = 1;
	free(*line);
	get_next_line(0, line);
	assign_room(room, *line);
	(*room)->state = start_end_state;
}

void	get_rooms(t_rlist **list)
{
	char	*line;
	t_room	*room;
	t_rlist	*temp;

	get_next_line(0, &line);
	while (!ft_strchr(line, '-'))
	{
		if (line[0] != '#')
			assign_room(&room, line);
		else if (line[1] == '#' && (line[2] == 's' || line[2] == 'e'))
			assign_start_end_room(&room, &line);
		if (room)
			add_room_list(room, list);
		room = NULL;
		free(line);
		get_next_line(0, &line);
	}
	get_links(*list, line);
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

void	get_links(t_rlist *list, char *line)
{
	char	**split;
	t_room	*r1;
	t_room	*r2;
	t_rlist	*temp;

	while (*line) //also must stop when nonsense is entered
	{
		if (line[0] != '#')
		{
			split = ft_strsplit(line, '-');
			r1 = NULL;
			r2 = NULL;
			temp = list;
			while (temp)
			{
				if (r1 && r2)
					break;
				if (!ft_strcmp(split[0], temp->room->name))
					r1 = temp->room;
				else if (!ft_strcmp(split[1], temp->room->name))
					r2 = temp->room;
				temp = temp->next;
			}
			check_link(r1, r2);
		}
		free(line);
		get_next_line(0, &line);
		ft_arrdel(&split);
	}
	free(line);
}
