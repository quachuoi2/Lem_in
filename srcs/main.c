/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/04 11:41:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			CROSSED;
int			best_p_count;
int			best_line_count;
int			g_ant;
t_path		*best_paths[MAGIC_NUMBER];
t_rlist		*hash_table;

int	main()
{
	int		fd = 0;
	int		insta = 0;
	t_rlist	*list;
	t_room	*start;
	t_edge	start_edge;

	// fd = 0;
	// fd = open("testmap/valid/big_sup/map_big_sup_9", O_RDONLY);
	fd = open("testmap/oneline", O_RDONLY);
	hash_table = ft_memalloc(sizeof(t_rlist) * HASH_SIZE);
	initialize_var(&list);
	read_map(&list, &start, fd);
	set_edge(&start_edge, start, start, 0);
	while(bfs(&start_edge))
	{
		lemme_in(start, g_ant);
		if (insta == 0)
			insta = instant_finish(g_ant, list);
	}
	start->ant = g_ant;
	exotic_ant_travelers(g_ant);
	// printf("line count: %d\n", best_line_count);
	free_everything(list);
	return (0);
}
