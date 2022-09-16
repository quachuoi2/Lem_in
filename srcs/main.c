/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/16 16:01:40 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	g_final_idx;

int	main()
{
	int		ant_num;
	int		fd;
	t_rlist	*list;
	t_room	*start;

	fd = open("./testmap/cross", O_RDONLY);
	fd = 0;
	list = NULL;
	get_data(&ant_num, fd, &list);
	check_start_end_room(list, &start);
	bfs(start, ant_num);
	// lemme_in(start, path, ant_num);

	printf("%s - ", start->name);
	t_room *temp;
	while (start->links)
	{
		temp = start->links->room;
		if (temp->forward)
		{
			while (temp->state != END_ROOM)
			{
				printf("%s - ", temp->name);
				temp = temp->forward->to;
			}
		}
		start->links = start->links->next;
	}
	printf("%s\n", temp->name);
	//free_everything(list);
	//free path
	return (0);
}
