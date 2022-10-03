/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/03 04:18:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int CROSSED = 1;

static void print_path(t_room *start)
{
	while (start->edge)
	{
		if (start->edge->flow == 1)
		{
			t_room *room = start->edge->to;
			printf("%s - ", start->name);
			while (room->state != END_ROOM)
			{
				printf("%s - ", room->name);
				room = room->next;
			}
			printf("%s\n", room->name);
		}
		start->edge = start->edge->next;
	}
}

static void	print_path_2(t_path **paths, int p_count)
{
	int i = 0;
	while (i < p_count)
	{
		if (paths[i]->ant_count > 0)
		{
			int j = 0;
			while (j < paths[i]->steps - 1)
			{
				printf("%s - ", paths[i]->huone[j]->name);
				j++;
			}
			printf("%s = %d\n", paths[i]->huone[j]->name, paths[i]->steps);
			i++;
		}
		else
			return;
	}
}

int	main()
{
	int		ant_num;
	int		fd;
	t_rlist	*list;
	t_room	*start;
	t_edge	start_edge;
	int		best_p_count;
	int		best_line_count;
	t_path	*best_paths[MAGIC_NUMBER];

	fd = 0;

	list = NULL;
	get_data(&ant_num, fd, &list);
	check_start_end_room(list, &start);
	start_edge.from = start;
	start_edge.to = start;
	start_edge.crossed = 0;
	best_line_count = 0;
	best_p_count = 0;
	int insta;
	int path_type;
	while((path_type = bfs(&start_edge)))
	{
		// printf("PT: %d\n", path_type);
		insta = lemme_in(start, best_paths, &best_line_count, &best_p_count, ant_num);
		if (insta == -1)
			break;
	}
	// if (insta != -1)
		// print_path_2(best_paths, best_p_count);
	printf("line count: %d\n", best_line_count);
	// printf("\n");
	// print_path(start);

	free_everything(list, best_paths, best_p_count);
	return (0);
}
