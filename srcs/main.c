/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 13:19:24 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			g_crossed;
int			g_ant;
int			g_best_path_count;
int			g_best_line_count;
t_path		*g_best_paths[MAGIC_NUMBER];
t_rlist		g_hash_table[HASH_SIZE];
t_room		*g_source;
t_room		*g_sink;
char		*g_map;

int	main(void)
{
	int		fd;
	int		insta_finish;
	int		path_found;
	t_edge	start_edge;

	fd = 0;
	init_global(&path_found);
	insta_finish = 0;
	read_map(fd);
	set_edge(&start_edge, g_source, g_source, 0);
	while (bfs(&start_edge))
	{
		lemme_in();
		if (insta_finish == 0)
			insta_finish = instant_finish();
		path_found++;
	}
	g_source->ant = g_ant;
	check_start_end_reachable(path_found);
	exotic_ant_travelers();
	free_everything();
	return (0);
}
	// printf("%d\n", g_best_line_count);
