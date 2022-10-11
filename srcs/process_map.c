/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:17:37 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 17:20:28 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

static void	process_line(char *line, int *link_stage)
{
	static int	start_end;

	if (line[0] != '#')
	{
		check_empty_line(line);
		if (assign_ants(line))
			return ;
		if (*link_stage == 1 || ft_strchr(line, '-'))
		{
			assign_edge(line);
			*link_stage = 1;
		}
		else
		{
			assign_room(line, start_end);
			start_end = NORMAL_ROOM;
		}
	}
	else
		read_command_comments(line, &start_end);
}

static void	process_map(int ret)
{
	int			link_stage;
	t_line		line;
	char		current_line[500];

	line.start = 0;
	line.end = 0;
	link_stage = 0;
	while (line.start < ret)
	{
		line.index = 0;
		while (g_map[line.end] != '\n' && line.end < ret)
			current_line[line.index++] = g_map[line.end++];
		current_line[line.index] = 0;
		process_line(current_line, &link_stage);
		line.end++;
		line.start = line.end;
	}
	check_missing_start_end();
	check_link_exist(link_stage);
}

void	read_map(void)
{
	int		ret;

	ret = read(0, g_map, STRING_AMOUNT);
	insurance_reading(&ret);
	check_empty_file();
	process_map(ret);
}
