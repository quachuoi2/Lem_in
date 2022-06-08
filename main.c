/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/08 03:21:59 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	int		ant_num;
	t_rlist	*list;
	t_rlist	*temp;

	list = NULL;
	get_ants(&ant_num);
	get_rooms(&list);
	free_everything(list);
	return (0);
}

/*	print list
 	while (list)
	{
		printf("%s\n", list->room->name);
		list = list->next;
	} */


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