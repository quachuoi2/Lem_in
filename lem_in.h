/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/13 23:57:19 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libftprintf.h"
# include "get_next_line.h"
# include <stdio.h> // delet nao

# define START_ROOM -1
# define NORMAL_ROOM 0
# define END_ROOM 1

typedef struct s_room t_room;
typedef struct s_rlist t_rlist;

struct s_room
{
	char	*name;
	int		coord_x;
	int		coord_y;
	int		se_state;
	//int		count_state;
	//int		link_count;
	t_rlist	*links;
};

struct s_rlist
{
	t_room	*room;
	t_rlist	*next;
};

//get.c
void	get_ants(int *ants_num, int fd);
void	get_rooms(t_rlist **list, int fd);
void	get_links(t_rlist *list, char *line, int fd);

//rlist.c
void	add_room_list(t_room *room, t_rlist **list);

//utilities.c
void	free_everything(t_rlist *list);
void	set_start_room(t_room **start, t_rlist *list);

//algo.c
int	count_routes(t_room *room);

#endif