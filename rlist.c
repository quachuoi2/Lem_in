/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 07:43:59 by qnguyen           #+#    #+#             */
/*   Updated: 2022/05/23 07:47:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_room_list(t_room *room, t_rlist **list)
{
	t_rlist	*current;

	current = (t_rlist *)malloc(sizeof(t_rlist));
	current->room = room;
	current->next = *list;
	*list = current;
}
