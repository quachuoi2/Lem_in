/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/19 22:00:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_room_list(t_room *room, t_rlist **list)
{
	t_rlist	*current;

	current = (t_rlist *)malloc(sizeof(t_rlist));
	current->room = room;
	current->next = *list;
	*list = current;
}

//deletable below
void	print_room_links(t_rlist *list)
{
 	char *line;
	t_rlist *temp;

	printf("room to show links: \n");
	get_next_line(0, &line);
	temp = list;
	while (temp)
	{
		if (!ft_strcmp(line, temp->room->name))
		{
			while (temp->room->links)
			{
				printf("links: ");
				printf("%s, ", temp->room->links->room->name);
				printf("\n");
				temp->room->links = temp->room->links->next;
			}
		}
		temp = temp->next;
	}
}

void track_one_route(t_room	*start)
{
	while (start->state != END_ROOM)
	{
		printf("%s - ", start->name);
		t_rlist *temp = start->links;
		int max_y = temp->room->coord_y;
		int min_x = temp->room->coord_x;

		while (temp)
		{
			if (temp->room->coord_y > max_y)
			{
				max_y = temp->room->coord_y;
				min_x = temp->room->coord_x;
			}
			temp = temp->next;
		}
		temp = start->links;
		while (temp)
		{
			if (temp->room->coord_y == max_y && temp->room->coord_x < min_x)
				min_x = temp->room->coord_x;
			temp = temp->next;
		}
		while (start->links)
		{
			if (start->links->room->coord_x == min_x && start->links->room->coord_y == max_y)
			{
				start = start->links->room;
				break;
			}
			start->links = start->links->next;
		}
	}
	printf("%s\n", start->name);
}

void	print_path(t_path *path, int last_path)
{
	int i = 0;

	printf("\n");
	while (i < last_path)
	{
		int j = 0;
		while (j < path[i].steps)
		{
			printf("%s - ", path[i].room[j]->name);
			j++;
		}
		printf("\n");
		i++;
	}
}
