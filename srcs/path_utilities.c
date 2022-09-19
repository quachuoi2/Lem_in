/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:26:07 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/18 21:37:07 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_path_groups(t_path_group *group)
{
	group->tol_step = 0;
	group->path_count = 0;
	group->line_count = 0;
	group->group = ft_memalloc(sizeof(int) * MAGIC_NUMBER);
}

void	adjust_path_group(t_path_group *cur, t_path *path, int *path_idx)
{
	cur->group[cur->path_count] = *path_idx;
	cur->tol_step += path[*path_idx].steps;
	cur->path_count++;
	(*path_idx)++;
}

void	assign_best_group(t_path_group *best, t_path_group *cur)
{
	int	i;

	best->line_count = cur->line_count;
	best->path_count = cur->path_count;
	best->tol_step = cur->tol_step;
	i = 0;
	while (i < best->path_count)
	{
		best->group[i] = cur->group[i];
		i++;
	}
}

int	path_clear(t_edge **rev_edge, int i)
{
	int j;
	int ret = 1;
	char *s, *t;
	int f, p;

	j = 0;
	//printf("%s -> %s = %d\n", rev_edge[j]->from->name, rev_edge[j]->to->name, rev_edge[j]->flow);
	printf("re: %s - ", rev_edge[j]->from->name);
	while (++j < i)
	{
		//printf("%s -> %s = %d\n", rev_edge[j]->from->name, rev_edge[j]->to->name, rev_edge[j]->flow);
		printf("%s - ", rev_edge[j]->from->name);
		if (ret == 1 && rev_edge[j]->to->path_idx != -1)
		{
			s = rev_edge[j + 1]->from->name;
			t = rev_edge[j + 1]->to->name;
			p = rev_edge[j + 1]->from->path_idx;
			f = rev_edge[j + 1]->flow;
			if (f == -1)
				ret = 2;
			else
				ret = 0;
		}
	}
	printf("%s\n", rev_edge[j - 1]->to->name);
	if (ret == 0)
		printf("clahsed at room: %s -> %s = %d\n", s, t, f);
	return (ret);
}

void	augment(t_edge **rev_edge, int i, int path_idx)
{
	t_room	*room;

	//printf("%s - ", rev_edge[i]->to->name);

	t_edge *temp = rev_edge[i]->to->forward_list;
	while (temp->to != rev_edge[i]->from)
		temp = temp->next;
	temp->flow = 1;
	while (i > 0)
	{
		room = rev_edge[i]->from;
		temp = room->forward_list;
		while (temp->to != rev_edge[i - 1]->from) // to set the forward edge flow to 1 //find a better way to do this instead of looping through all the forward links (hash map?)
			temp = temp->next;
		temp->flow = 1;

		room->backward = new_edge(rev_edge[i]->from, rev_edge[i]->to);
		room->backward->flow = -1;
		room->occupied = OCCUPIED;
		room->path_idx = path_idx;
		//printf("%s - ", rev_edge[i]->from->name);
		i--;
	}
	//printf("%s\n", rev_edge[i]->from->name);
}

int conclude_path(t_edge *rev_queue, int revq_idx, t_path *path, int path_idx)
{
	int step_count;
	int i = 0;
	t_room *current_tar;
	t_edge *rev_edge[revq_idx];

	step_count = 1;
	current_tar = rev_queue[revq_idx].to;
	rev_edge[i++] = &rev_queue[revq_idx];
	while (rev_queue[revq_idx].from->state != START_ROOM) //retrace the path found
	{
		if (rev_queue[revq_idx].from == current_tar)
		{
			rev_edge[i++] = &rev_queue[revq_idx];
			current_tar = rev_queue[revq_idx].to;
			step_count++;
		}
		revq_idx--;
	}
	if (path_clear(rev_edge, i) == 0)
		return (0);
	augment(rev_edge, i - 1, path_idx);
	path[path_idx].steps = step_count;
	path[path_idx].ant_count = 0;
	return (1);
}
