/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/22 19:36:31 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int CROSSED = 1;
t_path_group best;

static void print_path(t_room *start)
{
	if (start->state == END_ROOM)
	{
		printf("%s\n", start->name);
		return ;
	}
	t_edge *temp = start->forward_list;
	while (temp)
	{
		if (temp->flow == USED_FORWARD)
		{
			printf("%s - ", start->name);
			print_path(temp->to);
		}
		temp = temp->next;
	}
}

int	main()
{
	int		ant_num;
	int		fd;
	t_rlist	*list;
	t_room	*start;
	t_edge *start_edge = ft_memalloc(sizeof(t_edge));

	fd = 0;
	fd = open("./testmap/cross", O_RDONLY);
	fd = open("./testmap/extra/augment_4.map", O_RDONLY);

	list = NULL;
	get_data(&ant_num, fd, &list);
	check_start_end_room(list, &start);
	start_edge->from = start;
	start_edge->to = start;
	start_edge->crossed = 0;
	init_path_groups(&best);
	int time = 1;
	while(bfs(start_edge, ant_num))
	 	printf("\nran %d time\n", time++);
	printf("\n");
	printf("\n");
	print_path(start);
	//free_everything(list);
	//free path
	return (0);
}
