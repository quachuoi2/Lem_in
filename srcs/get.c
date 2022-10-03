/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:05:33 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/03 07:47:23 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_data(int *ants_num, int fd, t_rlist **list)
{
	char	*line;

	get_next_line(fd, &line);
	check_ants(line);
	*ants_num = ft_atoi(line);
	// printf("%s\n", line); //print map
	free(line);
	get_rooms(list, fd);
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
		// printf("%s\n", line); //print map
		free(line);
	}
	while (*line) //also must stop when nonsense is entered
	{
		// printf("%s\n", line); //print map
		if (*line != '#')
			get_links(*list, line, fd);
		free(line);
		if (get_next_line(fd, &line) == DONE_READ)
			break;
	}
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
		assign_edge(r1, r2);
	}
	ft_arrdel(&split);
}
