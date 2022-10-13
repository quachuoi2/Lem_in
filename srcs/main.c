/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/13 13:12:52 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int			g_crossed;
int			g_ant;
int			g_best_path_count;
int			g_best_line_count;
t_path		*g_best_paths[MAGIC_NUMBER];
t_rlist		g_hash_table[HASH_SIZE];
t_room		*g_source;
t_room		*g_sink;
char		*g_map;

int	main(int argc, char **argv)
{
	int		path_found;
	t_edge	start_edge;
	t_flags	flags;

	init_global(&path_found, &flags);
	check_options(argc, argv, &flags);
	read_map();
	set_edge(&start_edge, g_source, g_source, 0);
	while (bfs(&start_edge))
	{
		lemme_in();
		path_found = 1;
	}
	g_source->ant = g_ant;
	check_start_end_reachable(path_found);
	handle_options(&flags);
	free_everything();
	return (0);
}
