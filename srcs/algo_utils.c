/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/05 09:00:47 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	count_step(t_room *room)
{
	int	i;

	i = 1;
	while (room->state != END_ROOM)
	{
		room->step_count = i++;
		room = room->next;
	}
	return (i);
}

int	instant_finish(t_rlist *list)
{
	int	i;
	int	j;

	i = 0;
	while (i < best_p_count)
	{
		if (best_paths[i]->huone[0]->state == END_ROOM)
		{
			j = 0;
			while (j <= g_ant)
				printf("L%d-%s ", j++, best_paths[i]->huone[0]->name);
			printf("\n");
			free_everything(list);
			exit (0);
		}
		i++;
	}
	return (-1);
}
