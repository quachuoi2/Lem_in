/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/01 09:58:48 by qnguyen          ###   ########.fr       */
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

t_edge	*add_elist(t_room *from_room, t_room *to_room)
{
	t_edge *new;

	new = ft_memalloc(sizeof(t_edge));
	set_edge(new, from_room, to_room, 0);
	new->next = from_room->edge;
	from_room->edge = new;
	return (new);
}

void	set_edge(t_edge *edge, t_room *from, t_room *to, int flow)
{
	edge->from = from;
	edge->to = to;
	edge->flow = flow;
	edge->crossed = 0;
}
