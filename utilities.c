/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/13 21:17:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_everything(t_rlist *list)
{
	t_rlist	*temp;
	t_rlist	*temp2;

	while (list)
	{
		temp = list->next;
		free(list->room->name);
		while (list->room->links)
		{
			temp2 = list->room->links->next;
			free(list->room->links);
			list->room->links = temp2;
		}
		free(list->room);
		free(list);
		list = temp;
	}
}

void	set_start_room(t_room **start, t_rlist *list)
{
	while (list->room->se_state != START_ROOM)
		list = list->next;
	*start = list->room;
}
