/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:56:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 10:45:43 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* void	print_path_ant_count(t_path **path, int p_count, int line)
{
	int	i = 0;

	printf("\nlc: %d\n", line);
	printf("p: ");
	while (i < p_count - 1)
	{
		printf("%d  ", i);
		i++;
	}
	printf("%d\n", i);
	i = 0;
	printf("a: ");
	while (i < p_count - 1)
	{
		printf("%d  ", path[i]->ant_count);
		i++;
	}
	printf("%d\n", path[i]->ant_count);
} */

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
			path_idx++; //move through the paths with the same amount of steps
		path[step]->ant_count++;
		step++;
		max_ant--;
	}
	// print_path_ant_count(path, p_count, line);
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
			// printf("%s - ", room->name);
			g_best_paths[path_idx]->huone[room_idx] = room;
			room_idx++;
			room = room->next;
		}
		path_idx++;
		// printf("\n");
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
			path[p_count]->ant_count = 0;
			path[p_count]->total_steps = count_step(temp->to);
			path[p_count]->huone
				= ft_memalloc(sizeof(t_room *) * path[p_count]->total_steps);
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
		// printf("%d < %d\n", line_count, g_best_line_count);
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
