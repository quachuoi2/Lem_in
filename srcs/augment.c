/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:07:30 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 12:51:46 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	delete_backward_edge(t_edge *rev_edge, int i)
{
	delete_forward_room(rev_edge[i].from);
	if (i > 0 && rev_edge[i - 1].flow == BACKWARD)
		delete_prev_room(rev_edge[i].from);
}

static void	mixed_augment(t_edge *rev_edge, int r_i)
{
	int	i;
	int	step_count;

	i = r_i;
	step_count = 1;
	// printf("augment: ");
	while (i > -1)
	{
		// printf("%s - ", rev_edge[i].to->name);
		if (rev_edge[i].flow == BACKWARD)
			delete_backward_edge(rev_edge, i);
		else
		{
			if (i < r_i && rev_edge[i + 1].flow == BACKWARD)
				step_count = rev_edge[i].to->steps + 1;
			rev_edge[i].from->steps = step_count++;
			if (i > 0 && rev_edge[i - 1].flow == BACKWARD)
				delete_prev_room(rev_edge[i].from);
			rev_edge[i].to->next = rev_edge[i].from;
			rev_edge[i].from->prev = rev_edge[i].to;
			set_flow(rev_edge[i].to->edge, rev_edge[i].from, USED_FORWARD);
		}
		i--;
	}
	// printf("%s\n", rev_edge[i + 1].from->name);
}

static void	pure_forward_augment(t_edge *rev_edge, int r_i)
{
	int	step_count;

	step_count = 1;
	// printf("augment: ");
	while (r_i > -1)
	{
		// printf("%s - ", rev_edge[r_i].to->name);
		set_flow(rev_edge[r_i].to->edge, rev_edge[r_i].from, USED_FORWARD);
		rev_edge[r_i].from->prev = rev_edge[r_i].to;
		rev_edge[r_i].to->next = rev_edge[r_i].from;
		rev_edge[r_i].from->steps = step_count++;
		r_i--;
	}
	// printf("%s\n", rev_edge[r_i + 1].from->name);
}

int	augment(t_edge *rev_edge, int r_i, t_room *old_long_room, int backward)
{
	if (old_long_room != 0)
		remove_old_longer_path(old_long_room);
	if (backward == BACKWARD)
	{
		mixed_augment(rev_edge, r_i - 1);
		return (BACKWARD);
	}
	else
		pure_forward_augment(rev_edge, r_i - 1);
	return (USED_FORWARD);
}
