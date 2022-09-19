/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/18 21:30:59 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int VISITED = 1;
t_path_group best;

int	main()
{
	int		ant_num;
	int		fd;
	t_rlist	*list;
	t_room	*start;
	t_edge *start_edge = ft_memalloc(sizeof(t_edge));

	fd = 0;
	fd = open("./testmap/cross", O_RDONLY);
	list = NULL;
	get_data(&ant_num, fd, &list);
	check_start_end_room(list, &start);
	start_edge->from = start;
	start_edge->to = start;
	bfs(start_edge, ant_num);
	bfs(start_edge, ant_num);
	//bfs(start, ant_num);
	// lemme_in(start, path, ant_num);

/* 	printf("res: %s - ", start->name);
	while (start->forward_list)
	{
		t_edge *temp = start->forward_list;
		while (temp)
		{
			if (temp->flow == 1)
			{
				printf("%s - ", temp->to->name);
				temp = temp->to->forward_list;
			}
			else
				temp = temp->next;
		}
		start->forward_list = start->forward_list->next;
	} */
	//free_everything(list);
	//free path
	return (0);
}
