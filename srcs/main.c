/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/25 18:29:08 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int CROSSED = 1;

static void print_path2(t_room *start)
{
	while (start->forward_list)
	{
		if (start->forward_list->flow == 1)
		{
			printf("%s - ", start->name);
			t_room *room = start->forward_list->to;
			while (room->state != END_ROOM)
			{
				printf("%s - ", room->name);
				room = room->next;
			}
			printf("%s\n", room->name);
		}
		start->forward_list = start->forward_list->next;
	}
}

int	main()
{
	int		ant_num;
	int		fd;
	t_rlist	*list;
	t_room	*start;
	t_edge start_edge;

	fd = open("./testmap/extra/augment_1.map", O_RDONLY);
	fd = open("./testmap/cross", O_RDONLY);
	fd = 0;

	list = NULL;
	get_data(&ant_num, fd, &list);
	check_start_end_room(list, &start);
	start_edge.from = start;
	start_edge.to = start;
	start_edge.crossed = 0;
	int time = 1;
	while(bfs(&start_edge, ant_num))
	{
		// line_count(&cur, path, ant);
		// if (best.line_count > cur.line_count || best.line_count == 0)
		// 	assign_best_group(&best, &cur);
		// printf("LC: %d\n", best.line_count);
	 	printf("\nran %d time\n", time++);
	}
	printf("\n");
	printf("\n");
	print_path2(start);

	//free_everything(list);
	//free path
	return (0);
}
