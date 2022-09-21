/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 21:26:07 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/21 22:17:35 by qnguyen          ###   ########.fr       */
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

static int	path_clear_with_printing(t_edge **rev_edge, int i)
{
	int j;
	int ret = 1;
	t_room *fail;
	j = 0;

	printf("%s -> %s = %d\n", rev_edge[j]->from->name, rev_edge[j]->to->name, rev_edge[j]->flow);
	//printf("re: %s - ", rev_edge[j]->from->name);
	while (++j < i)
	{
		printf("%s -> %s = %d\n", rev_edge[j]->from->name, rev_edge[j]->to->name, rev_edge[j]->flow);
		// printf("%s - ", rev_edge[j]->from->name);
		if (rev_edge[j]->from->prev && rev_edge[j]->from->prev == rev_edge[j]->to) // if there is a backward edge that matches this rev_edge ->fail
		{
			ret = 0;
			fail = rev_edge[j]->from;
			//return (0);
		}
	}
	// printf("%s\n", rev_edge[j - 1]->to->name);
	if (ret == 0)
		printf("clahsed at room: %s\n", fail->name);
	return (ret);
}

static int	path_clear_actual(t_edge **rev_edge, int i)
{
	int j;

	j = 0;
	while (++j < i)
		if (rev_edge[j]->from->prev && rev_edge[j]->from->prev == rev_edge[j]->to) // if there is a backward edge that matches this rev_edge ->fail
			return (0);
	return (1);
}

static void	unset_flow(t_edge *list, t_room *target_room)
{
	while (list->to != target_room) //loop to forward links to find the room to remove flow
		list = list->next;
	list->flow = UNUSED_FORWARD;
}

void	delete_residual_edge(t_edge *edge)
{
	unset_flow(edge->from->forward_list, edge->to);
	edge->to->prev = 0;
}

int	augment(t_edge **rev_edge, int rev_count, int path_idx)
{
	t_room	*room;
	t_edge	*temp;
	int		backward_edge_used;
	int		i;

	i = 0;
	backward_edge_used = 1;
	while (i <= rev_count)
	{
		if (rev_edge[i]->flow == BACKWARD)
		{
			delete_residual_edge(rev_edge[i]);
			backward_edge_used = 0;
		}
		else
		{
			temp = rev_edge[i]->to->forward_list;
			while (temp) // to set the forward edge flow to 1 //find a better way to do this instead of looping through all the forward links (hash map?)
			{
				if (temp->to == rev_edge[i]->from)
					temp->flow = USED_FORWARD; //this one is the edge to the new found room
				else if (temp->flow == USED_FORWARD && temp->from->state != START_ROOM)
				{
					temp->flow = UNUSED_FORWARD; // delete forward flow of the old path
					temp->to->up_for_grabz = -1;
					temp->to->prev = 0;
				}// might not be needed
				temp = temp->next;
			}
			room = rev_edge[i]->from;
			if (!room->prev)
				room->prev = rev_edge[i]->to;
			room->up_for_grabz = 0;
		}
		printf("%s - ", rev_edge[i]->from->name);
		i++;
	}
	printf("%s\n", rev_edge[i - 1]->to->name);
	return (backward_edge_used);
}

int conclude_path(t_edge *rev_queue, int revq_idx, t_path *path, int path_idx)
{
	int step_count;
	int i = 0;
	int	path_type;
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
	if (path_clear_with_printing(rev_edge, i) == 0)
	// if (path_clear_actual(rev_edge, i) == 0)
		return (0);
	printf("path found UwU\n");
	if (augment(rev_edge, i - 1, path_idx)) //if used only foward edges
		path[path_idx].steps = step_count;
	path[path_idx].ant_count = 0;
	return (1);
}
