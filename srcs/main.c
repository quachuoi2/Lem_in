/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:27:08 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/22 09:26:13 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	main()
{
	int		ant_num;
	int		fd;
	t_rlist	*list;
	t_room	*start;

	fd = open("./testmap/big_map", O_RDONLY);
	//fd = open("./testmap/mep", O_RDONLY);
	list = NULL;
	get_data(&ant_num, fd, &list);
	check_start_end_room(list, &start);
	lemme_in(start);
	free_everything(list);
	return (0);
}
