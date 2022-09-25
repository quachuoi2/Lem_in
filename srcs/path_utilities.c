/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:26:07 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/25 03:22:05 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	path_count(t_room *room, t_path *path)
{
	int	count;
	t_room *temp;

	while (room->forward_list)
	{
		if (room->forward_list->flow == 1)
		{
			path->huone[0] = room; //huone[0] = start
			temp = room->forward_list->to;
			while (temp->next->state != END_ROOM)
			{
				path->huone[temp->step_count] = temp->next;
				temp = temp->next;
			}
		}
		room->forward_list = room->forward_list->next;
	}
}
