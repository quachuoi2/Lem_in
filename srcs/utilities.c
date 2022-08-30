/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/30 17:18:01 by qnguyen          ###   ########.fr       */
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

void	initialize_best_path(int **best_path, int path_idx)
{
	*best_path = ft_memalloc(sizeof(int) * (path_idx + 1));
	int i = 0;
	while (i < path_idx)
	{
		(*best_path)[i] = i;
		i++;
	}
	(*best_path)[i] = -1;
}


void	initialize_paths(t_path **path)
{
	int	i;

	(*path) = malloc(sizeof(t_path) * NUM_OF_PATH);
	i = 0;
	while (i < NUM_OF_PATH)
		(*path)[i++].room = ft_memalloc(sizeof(t_room *) * NUM_OF_ROOM_PER_PATH);
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

void	print_path(t_path *path, int last_path)
{
	int i = 0;

	printf("all routes: \n");
	while (i < last_path)
	{
		int j = 0;
		while (j < path[i].steps)
		{
			printf("%s - ", path[i].room[j]->name);
			j++;
		}
		printf("%s\n", path[i].room[j]->name);
		i++;
	}
}

void	print_max_flow_path(int *best_path)
{
	int i = 0;
	while (best_path[i] != -1)
	{
		printf("%d-", best_path[i]);
		i++;
	}
	printf("\n");
}
