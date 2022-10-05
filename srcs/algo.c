/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 20:56:00 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/05 09:00:04 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_path_ant_count(t_path **path, int p_count)
{
	int	i = 0;

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
}

static int	count_lines(t_path **path, int p_count)
{
	int	path_idx;
	int	line;
	int	step;
	int max_ant;

	path_idx = 0;
	step = 0;
	line = path[0]->steps;
	max_ant = g_ant;
	while (max_ant > 0)
	{
		if (step > path_idx)
		{
			step = 0;
			line++;
		}
		while (path_idx + 1 < p_count && line >= path[path_idx + 1]->steps && step == 0)  //move through all the paths with the same amt of steps
			path_idx++;
		path[step]->ant_count++;
		step++;
		max_ant--;
	}
	// printf("\nlc: %d\n", line);
	// print_path_ant_count(path, p_count);
	return (line);
}

static void	set_best_paths(t_path **paths, int p_count)
{
	int		i;
	int		j;
	t_room	*room;

	i = 0;
	while (i < p_count)
	{
		best_paths[i] = paths[i];
		j = 0;
		room = best_paths[i]->huone[j];
		while (j < best_paths[i]->steps)
		{
			// printf("%s - ", room->name);
			best_paths[i]->huone[j] = room;
			j++;
			room = room->next;
		}
		i++;
		// printf("\n");
	}
}

static int set_paths(t_room *start, t_path **path)
{
	int	p_count;
	t_edge *temp;

	p_count = 0;
	temp = start->edge;
	while (temp)
	{
		if (temp->flow == 1)
		{
			path[p_count] = (t_path *)ft_memalloc(sizeof(t_path));
			path[p_count]->ant_count = 0;
			path[p_count]->steps = count_step(temp->to);
			path[p_count]->huone = ft_memalloc(sizeof(t_room *) * path[p_count]->steps);
			path[p_count]->huone[0] = temp->to;
			temp->set = 1;
			p_count++;
		}
		temp = temp->next;
	}
	path[p_count] = NULL;
	return (p_count);
}

int	lemme_in(t_room *start)
{
	int				p_count;
	int				line_count;
	t_path			*paths[MAGIC_NUMBER];

	p_count = set_paths(start, paths);
	path_quicksort(paths, 0, p_count - 1);
	line_count = count_lines(paths, p_count);
	if (line_count < best_line_count || best_line_count == 0)
	{
		// printf("%d < %d\n", line_count, best_line_count);
		if (best_p_count != 0)
			free_path(best_paths, best_p_count);
		set_best_paths(paths, p_count);
		best_line_count = line_count;
		best_p_count = p_count;
	}
	else
		free_path(paths, p_count);
	return (line_count);
}
