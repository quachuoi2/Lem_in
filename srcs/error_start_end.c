/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_start_end.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:55:02 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 16:03:31 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_missing_start_end(void)
{
	if (!g_source || !g_sink)
	{
		if (g_source == NOT_FOUND)
			ft_printf("ERROR: Start room missing\n");
		if (g_sink == NOT_FOUND)
			ft_printf("ERROR: End room missing\n");
		teminate_program();
	}
}

void	check_duplicate_start_end(t_room *room, int room_state)
{
	if (room_state == START_ROOM && g_source != NULL)
	{
		ft_printf("ERROR: Duplicate start room found\n");
		free(room);
		teminate_program();
	}
	if (room_state == END_ROOM && g_sink != NULL)
	{
		ft_printf("ERROR: Duplicate end room found\n");
		free(room);
		teminate_program();
	}
}

void	check_start_end_reachable(int path_found)
{
	if (path_found == NOT_FOUND)
	{
		ft_printf("ERROR: There is no path to the end room\n");
		teminate_program();
	}
}

void	check_double_command_comment(int start_end)
{
	if (start_end != NORMAL_ROOM)
	{
		ft_printf("ERROR: Error on command input found\n");
		teminate_program();
	}
}
