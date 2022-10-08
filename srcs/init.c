/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:25:46 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 11:42:56 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_global(int *path_found)
{
	g_crossed = 1;
	g_ant = 0;
	g_best_line_count = 0;
	g_best_path_count = 0;
	g_source = NULL;
	g_sink = NULL;
	g_map = ft_memalloc(sizeof(char) * STRING_AMOUNT);
	*path_found = 0;
}

void	init_queue(t_queue *q, t_edge *start)
{
	q->queue[0] = start;
	q->remaining = 1;
	q->count = 1;
	q->idx = 0;
}

void	init_conclude_path_data(int *r_i, int *bckwrd_edge_used, t_room **old)
{
	*r_i = 0;
	*bckwrd_edge_used = 0;
	*old = NULL;
}
