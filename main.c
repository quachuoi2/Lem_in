/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/05/23 08:56:35 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	int		ant_num;
	t_rlist	*list;

	list = NULL;
	get_ants(&ant_num);
	get_rooms(&list);
/* 	while (list)
	{
		printf("%s\n", list->room->name);
		list = list->next;
	} */
	char *line;
	printf("room to show links: \n");
	get_next_line(0, &line);
	while (list)
	{
		if (!ft_strcmp(line, list->room->name))
		{
			while (list->room->links)
			{
				printf("links: ");
				printf("%s, ", list->room->links->room->name);
				printf("\n");
				list->room->links = list->room->links->next;
			}
		}
		list = list->next;
	}
/* 	while (list)
	{
		if (!ft_strcmp(list->room->name, "2"))
		{
			while (list->room->links)
			{
				printf("%s\n", list->room->links->room->name);
				list->room->links = list->room->links->next;
			}
		}
		list = list->next;
	} */
	return (0);
}
