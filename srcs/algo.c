/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:56:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 16:12:25 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static int	count_lines(t_path **path, int p_count)
{
	int	path_idx;
	int	line;
	int	step;
	int	max_ant;

	path_idx = 0;
	step = 0;
	line = path[0]->total_steps;
	max_ant = g_ant;
	while (max_ant > 0)
	{
		if (step > path_idx)
		{
			step = 0;
			line++;
		}
		while (path_idx + 1 < p_count
			&& line >= path[path_idx + 1]->total_steps && step == 0)
			path_idx++;
		path[step]->ant_count++;
		step++;
		max_ant--;
	}
	return (line);
}

static void	set_best_paths(t_path **paths, int p_count)
{
	int		path_idx;
	int		room_idx;
	t_room	*room;

	path_idx = 0;
	while (path_idx < p_count)
	{
		g_best_paths[path_idx] = paths[path_idx];
		room_idx = 0;
		room = g_best_paths[path_idx]->huone[room_idx];
		while (room_idx < g_best_paths[path_idx]->total_steps)
		{
			g_best_paths[path_idx]->huone[room_idx] = room;
			room_idx++;
			room = room->next;
		}
		path_idx++;
	}
}

static int	set_paths(t_path **path)
{
	int		p_count;
	t_edge	*temp;

	p_count = 0;
	temp = g_source->edge;
	while (temp)
	{
		if (temp->flow == 1)
		{
			path[p_count] = (t_path *)ft_memalloc(sizeof(t_path));
			check_malloc((void *)path[p_count]);
			path[p_count]->ant_count = 0;
			path[p_count]->total_steps = count_step(temp->to);
			path[p_count]->huone
				= (t_room **)
				ft_memalloc(sizeof(t_room *) * path[p_count]->total_steps);
			check_malloc((void *)path[p_count]);
			path[p_count]->huone[0] = temp->to;
			p_count++;
		}
		temp = temp->next;
	}
	path[p_count] = NULL;
	return (p_count);
}

int	lemme_in(void)
{
	int				p_count;
	int				line_count;
	t_path			*paths[MAGIC_NUMBER];

	p_count = set_paths(paths);
	path_quicksort(paths, 0, p_count - 1);
	line_count = count_lines(paths, p_count);
	if (line_count < g_best_line_count || g_best_line_count == 0)
	{
		if (g_best_path_count != 0)
			free_path(g_best_paths, g_best_path_count);
		set_best_paths(paths, p_count);
		g_best_line_count = line_count;
		g_best_path_count = p_count;
	}
	else
		free_path(paths, p_count);
	return (line_count);
}
