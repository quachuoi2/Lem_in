/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:17:37 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/04 10:01:44 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	get_ants(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		check_ants_char(str[i++]);
	g_ant = ft_atoi(str);
	check_ant_amount();
	return (i + 1);
}

static void	get_links(t_rlist *list, char *line, int fd)
{
	char	**split;
	t_room	*r1;
	t_room	*r2;

	if (line[0] != '#')
	{
		split = ft_strsplit(line, '-');
		r1 = NULL;
		r2 = NULL;
		while (list && (!r1 || !r2))
		{
			if (!ft_strcmp(split[0], list->room->name)) //maybe hashing would increase the speed a bit
				r1 = list->room;
			else if (!ft_strcmp(split[1], list->room->name))
				r2 = list->room;
			list = list->next;
		}
		check_valid_room(r1, r2);
		assign_edge(r1, r2);
	}
	ft_arrdel(&split);
}

static void	process_line(t_rlist **list, char *line, int fd)
{
	static int	link_stage;
	static int	start_end;
	t_room		*room;
	t_rlist		*temp;

	room = NULL;
	if (line[0] != '#')
	{
		if (link_stage == 1 || ft_strchr(line, '-'))
		{
			get_links(*list, line, 0);
			link_stage = 1;
		}
		else
		{
			assign_room(&room, line, start_end);
			start_end = NORMAL_ROOM;
		}
	}
	else
		start_end = get_command(line);
	if (room)
		add_room_list(room, list);
}

static void	process_map(t_rlist **list, char *str, int ret, int fd)
{
	int		l_start;
	int		l_end;
	char	smol_line[500];
	int		i;

	l_start = get_ants(str);
	l_end = l_start;
	while (l_start < ret)
	{
		i = 0;
		while (str[l_end] != '\n' && l_end < ret)
		{
			smol_line[i] = str[l_end];
			i++;
			l_end++;
		}
		smol_line[i] = 0;
		process_line(list, smol_line, fd);
		l_end++;
		l_start = l_end;
	}
}

void	read_map(t_rlist **list, t_room **start, int fd)
{
	int		ret;
	int		total;
	char	*str;

	str = ft_memalloc(sizeof(char) * STRING_AMOUNT);
	ret = read(fd, str, STRING_AMOUNT - 1);
	total = insurance_reading(&str, ret, fd);
	process_map(list, str, total, fd);
	check_start_end_room(*list, start);
	str[total] = '\n';
	write (1, str, total + 1);
	free(str);
}
