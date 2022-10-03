/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/03 07:28:03 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		CROSSED;
int		best_p_count;
int		best_line_count;
t_path	*best_paths[MAGIC_NUMBER];

int	main()
{
	int		ant_num;
	int		fd = 0;
	int		insta = 0;
	t_rlist	*list;
	t_room	*start;
	t_edge	start_edge;

	initialize_var(&list);
	get_data(&ant_num, fd, &list);
	check_start_end_room(list, &start);
	set_edge(&start_edge, start, start, 0);
	while(bfs(&start_edge))
	{
		lemme_in(start, ant_num);
		if (insta == 0)
			insta = instant_finish(ant_num, list);
	}
	start->ant = ant_num;
	exotic_ant_travelers(ant_num);
	// printf("line count: %d\n", best_line_count);
	free_everything(list);
	return (0);
}
