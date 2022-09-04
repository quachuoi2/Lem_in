/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:29:54 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/30 22:39:52 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_start_end_room(t_rlist *list, t_room **start)
{
	int	end;

	end = 0;
	*start = NULL;
	while (list)
	{
		if (list->room->state == END_ROOM)
			end = 1;
		else if (list->room->state == START_ROOM)
			*start = list->room;
		list = list->next;
	}
	if (!end || !*start)
	{
		printf("where room\n");
		exit(0);
	}
}

void	check_ants(char *line)
{
	while (*line)
	{
		if (!ft_isdigit(*line))
		{
			printf("???\n");
			exit(0);
		}
		line++;
	}
}
