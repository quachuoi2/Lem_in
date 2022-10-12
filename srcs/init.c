/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 10:25:46 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/12 16:34:31 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	init_global(int *path_found, t_flags *flags)
{
	g_crossed = 1;
	g_ant = 0;
	g_best_line_count = 0;
	g_best_path_count = 0;
	g_source = NULL;
	g_sink = NULL;
	g_map = (char *)ft_memalloc(sizeof(char) * STRING_AMOUNT);
	check_malloc((void *)g_map);
	*path_found = 0;
	flags->line = 0;
	flags->nodistribution = 0;
	flags->nomap = 0;
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

void	init_ant_distr(t_ant_distr *distr)
{
	distr->str_size = STRING_AMOUNT;
	distr->line = (char *)ft_memalloc(sizeof(char) * distr->str_size);
	check_malloc(distr->line);
}
