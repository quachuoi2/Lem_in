/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/08 03:12:12 by qnguyen          ###   ########.fr       */
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
