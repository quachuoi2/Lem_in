/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 02:07:45 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 16:20:35 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_edge	*add_elist(t_room *from_room, t_room *to_room)
{
	t_edge	*edge;

	edge = (t_edge *)ft_memalloc(sizeof(t_edge));
	check_malloc((void *)edge);
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
}

void	set_tracer(t_tracer *tracer, int idx, int steps)
{
	tracer->idx = idx;
	tracer->steps = steps;
}

void	teminate_program(void)
{
	free_everything();
	exit(0);
}
