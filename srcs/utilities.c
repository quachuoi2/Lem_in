/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/22 15:32:38 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_room_list(t_room *room, t_rlist **list)
{
	t_rlist	*current;

	current = (t_rlist *)malloc(sizeof(t_rlist));
	current->room = room;
	current->next = *list;
	current->forw_list_created = 0;
	*list = current;
}

t_edge	*add_elist(t_room *from_room, t_room *to_room)
{
	t_edge *new;

	new = new_edge(from_room, to_room);
	new->next = from_room->forward_list;
	from_room->forward_list = new;
	return (new);
}

t_edge	*new_edge(t_room *from_room, t_room *to_room)
{
	t_edge *new;

	new = ft_memalloc(sizeof(t_edge));
	edge_assign(new, from_room, to_room, 0);
	new->next = NULL;
	return (new);
}

void	edge_assign(t_edge *edge, t_room *from, t_room *to, int flow)
{
	edge->from = from;
	edge->to = to;
	edge->flow = flow;
	edge->crossed = 0;
}

//deletable below
/*void	initialize_best_path(int **best_path)
{
	*best_path = ft_memalloc(sizeof(int) * (g_final_idx + 1));
	int i = 0;
	while (i < g_final_idx)
	{
		(*best_path)[i] = i;
		i++;
	}
	(*best_path)[i] = -1;
}

void	initialize_paths(t_path **path)
{
	int	i;

	(*path) = malloc(sizeof(t_path) * MAGIC_NUMBER);
	i = 0;
	while (i < MAGIC_NUMBER)
		(*path)[i++].room = ft_memalloc(sizeof(t_room *) * MAGIC_NUMBER);
}

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

void	print_path(t_path *path)
{
	int i = 0;

	printf("all routes: \n");
	while (i < g_final_idx)
	{
		int j = 0;
		printf("%d: ",i);
		while (j < path[i].steps)
		{
			printf("%s - ", path[i].room[j]->name);
			j++;
		}
		printf("%s\n", path[i].room[j]->name);
		i++;
	}
	printf("\n");
}

void	print_flow_path(t_path *path, int *flow_path, int mof)
{
	int i = 0;
	int sum = 0;
	if (mof == 0)
		printf("fg: ");
	else if (mof == 1)
		printf("mfg: ");
	else if (mof == 2)
		printf("RG:  ");
	else if (mof == 3)
		printf("tf:  ");
	while (flow_path[i] != -1)
	{
		printf("%d-", flow_path[i]);
		sum += path[flow_path[i]].steps;
		i++;
	}
	printf(" = %d (%d)\n\n", sum, i);
}

void	print_path_ant_count(t_path *path, int *best_path)
{
	int i = 0;
	while (best_path[i] != -1)
		printf("%d ", best_path[i++]);
	printf("\n");
	i = 0;
	while (best_path[i] != -1)
		printf("%d ", path[best_path[i++]].ant_count);
	printf("\n");
}
 */