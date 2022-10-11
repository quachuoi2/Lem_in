/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 17:20:16 by qnguyen          ###   ########.fr       */
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
	int		insta_finish;
	int		path_found;
	t_edge	start_edge;
	t_flags	flags;

	init_global(&path_found, &flags);
	check_options(argc, argv, &flags);
	insta_finish = 0;
	read_map();
	set_edge(&start_edge, g_source, g_source, 0);
	while (bfs(&start_edge))
	{
		lemme_in();
		if (insta_finish == 0)
			insta_finish = instant_finish();
		path_found = 1;
	}
	g_source->ant = g_ant;
	check_start_end_reachable(path_found);
	handle_options(&flags);
	free_everything();
	return (0);
}
