/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:29:54 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/04 11:34:36 by qnguyen          ###   ########.fr       */
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
		printf("Bad Start/End room\n");
		exit(0);
	}
}

void	check_ants_char(char c)
{
	if (!ft_isdigit(c))
	{
		printf("???\n");
		exit(0);
	}
}

void	check_ant_amount()
{
	if (g_ant < 1)
	{
		ft_printf("Bad ant amount\n");
		exit (0);
	}
}

void	check_valid_room(t_room *r1, t_room *r2)
{
	if (!r1 || !r2)
	{
		ft_printf("Bollocks link\n");
		exit (0);
	}
}

void	check_invalid_room_input(char **split)
{
	int i = 0;
	while (split[i])
	{
		if (i > 2)
		{
			ft_printf("Invalid room input\n");
			ft_arrdel(&split);
			exit (0);
		}
		i++;
	}
}

void	check_duplicate_room(int hash_result)
{
	if (hash_result == 0)
	{
		ft_printf("Duplicate rooms found\n");
		// free_stuff();
		exit(0);
	}
}