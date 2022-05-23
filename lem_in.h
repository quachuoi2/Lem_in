/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/05/23 07:54:04 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libftprintf.h"
# include "get_next_line.h"

# include <stdio.h> // delet nao

typedef struct s_room t_room;
typedef struct s_rlist t_rlist;

struct s_room
{
	char	*name;
	int		coord_x;
	int		coord_y;
	int		state;
	t_rlist	*links;
};

struct s_rlist
{
	t_room	*room;
	t_rlist	*next;
};

//get.c
void	get_ants(int *ants_num);
void	get_rooms(t_rlist **list);
void	get_links(t_rlist *list, char *line);

//rlist.c
void	add_room_list(t_room *room, t_rlist **list);

#endif