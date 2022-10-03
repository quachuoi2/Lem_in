/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   augment.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:07:30 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/02 12:25:45 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mixed_augment(t_edge *rev_edge, int rev_idx)
{
	int	i;
	int	step_count;

	i = rev_idx;
	step_count = 1;
	// printf("augment: ");
	while (i > -1)
	{
		// printf("%s - ", rev_edge[i].to->name);
		if (rev_edge[i].flow == BACKWARD)
		{
			delete_forward_room(rev_edge[i].from);
			if (i > 0 && rev_edge[i - 1].flow == BACKWARD)
				delete_prev_room(rev_edge[i].from); //rev_edge[i].from->step_count = 0;
		}
		else
		{
			if (i < rev_idx && rev_edge[i + 1].flow == BACKWARD) // if i = rev_idx -> uninitialized //maybe set it to some garbo value to skip the if check and remove int i
				step_count = rev_edge[i].to->step_count + 1;
			rev_edge[i].from->step_count = step_count++;
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

void	pure_forward_augment(t_edge *rev_edge, int rev_idx)
{
	int	step_count;

	step_count = 1;
	while (rev_idx > -1)
	{
		// printf("%s - ", rev_edge[rev_idx].to->name);
		set_flow(rev_edge[rev_idx].to->edge, rev_edge[rev_idx].from, USED_FORWARD);
		rev_edge[rev_idx].from->prev = rev_edge[rev_idx].to;
		rev_edge[rev_idx].to->next = rev_edge[rev_idx].from;
		rev_edge[rev_idx].from->step_count = step_count++;
		rev_idx--;
	}
	// printf("%s\n", rev_edge[rev_idx + 1].from->name);
}
