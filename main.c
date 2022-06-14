/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/14 06:31:52 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		ant_num;
	int		fd;
	t_rlist	*list;
	t_rlist	*temp;
	t_room	*start;

	/* if (argc < 2)
		return (write(1, "no input\n", 9)); */
	fd = open("z", O_RDONLY);
	list = NULL;
	get_ants(&ant_num, fd);
	get_rooms(&list, fd);
	set_start_room(&start, list);

	int temp_y = 0;
	while (start->se_state != END_ROOM)
	{
		printf("%s - ", start->name);
		while (start->coord_y > start->links->room->coord_y)
			start->links = start->links->next;
		start = start->links->room;
	}
	printf("%s\n", start->name);
	free_everything(list);
	return (0);
}

/* 	print links
	char *line;

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
	} */
