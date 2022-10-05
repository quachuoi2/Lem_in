/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/05 09:48:46 by qnguyen          ###   ########.fr       */
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

	// fd = open("testmap/oneline", O_RDONLY);
	// fd = open("testmap/valid/big_sup/map_big_sup_9", O_RDONLY);
	fd = 0;
	hash_table = ft_memalloc(sizeof(t_rlist) * HASH_SIZE);
	initialize_var(&list);
	read_map(&list, &start, fd);
	set_edge(&start_edge, start, start, 0);
	while(bfs(&start_edge))
	{
		lemme_in(start);
		if (insta == 0)
			insta = instant_finish(list);
	}
	start->ant = g_ant;
	exotic_ant_travelers();
	// printf("line count: %d\n", best_line_count);
	free_everything(list);
	return (0);
}
