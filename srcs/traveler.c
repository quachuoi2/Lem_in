/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traveler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 07:28:05 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/12 16:38:24 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	insert_ant(t_ant_distr *distr, char *room_name, int ant_num)
{
	int		i;
	char	str[50];
	char	*ant_num_str;

	ft_bzero((void *)str, 50);
	str[0] = 'L';
	i = 1;
	ant_num_str = ft_itoa(ant_num);
	ft_strcpy(str + i, ant_num_str);
	free(ant_num_str);
	while (str[i])
		i++;
	str[i++] = '-';
	ft_strcpy(str + i, room_name);
	while (str[i])
		i++;
	str[i++] = ' ';
	ft_strcat(distr->line, str);
	if (distr->line[distr->str_size - 1] != 0)
	{
		distr->str_size = distr->str_size * 2;
		double_str_size((void **)&distr->line, distr->str_size);
	}
}

static void	move_to_next(t_ant_distr *distr, t_room *room, t_room *next)
{
	if (room->ant != 0)
	{
		insert_ant(distr, next->name, room->ant);
		if (next != g_sink)
			next->ant = room->ant;
		else
			next->ant++;
		room->ant = 0;
	}
}

static void	first_step(t_ant_distr *distr,
	t_room *room, t_path *cur_path, int *cur_ant)
{
	room->ant = *cur_ant;
	(*cur_ant)++;
	cur_path->ant_count--;
	insert_ant(distr, room->name, room->ant);
}

void	exotic_ant_travelers(void)
{
	int			path_idx;
	int			room_idx;
	int			cur_ant;
	t_room		**room;
	t_ant_distr	distr;

	cur_ant = 1;
	init_ant_distr(&distr);
	while (g_sink->ant < g_ant)
	{
		path_idx = 0;
		distr.line[0] = 0;
		while (path_idx < g_best_path_count)
		{
			room = g_best_paths[path_idx]->huone;
			room_idx = g_best_paths[path_idx]->total_steps - 1;
			while (--room_idx >= 0)
				move_to_next(&distr, room[room_idx], room[room_idx + 1]);
			if (cur_ant <= g_ant && g_best_paths[path_idx]->ant_count > 0)
				first_step(&distr, room[0], g_best_paths[path_idx], &cur_ant);
			path_idx++;
		}
		ft_putendl(distr.line);
	}
	ft_memdel((void **)&distr.line);
}
