/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/03 05:02:09 by qnguyen          ###   ########.fr       */
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
	t_edge *edge;

	edge = ft_memalloc(sizeof(t_edge));
	set_edge(edge, from_room, to_room, 0);
	edge->next = from_room->edge;
	from_room->edge = edge;
	return (edge);
}

void	set_edge(t_edge *edge, t_room *from, t_room *to, int flow)
{
	edge->from = from;
	edge->to = to;
	edge->flow = flow;
	edge->crossed = 0;
	edge->set = 0;
}

void	initialize_var(t_rlist **list)
{
	CROSSED = 1;
	best_line_count = 0;
	best_p_count = 0;
	*list = NULL;
}