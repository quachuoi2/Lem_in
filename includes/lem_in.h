/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/21 22:22:48 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libftprintf.h"
# include "get_next_line.h"
# include <stdio.h> // delet nao

# define START_ROOM -2
# define END_ROOM -1
# define VACANT_ROOM 0
# define OCCUPIED_ROOM 1
# define NUM_OF_PATH 500
# define NUM_OF_ROOM_PER_PATH 500

typedef struct s_room t_room;
typedef struct s_rlist t_rlist;
typedef struct s_path t_path;

struct s_room
{
	int		coord_x;
	int		coord_y;
	int		state;
	int		crossed;
	char	*name;
	t_rlist	*links;
};

struct s_rlist
{
	t_room	*room;
	t_rlist	*next;
};

struct s_path
{
	int		steps;
	//t_room	*room;
	t_room	**room;
};

//get.c
void	get_data(int *ants_num, int fd, t_rlist **list);
void	get_rooms(t_rlist **list, int fd);
void	get_links(t_rlist *list, char *line, int fd);

//utilities.c
void	add_room_list(t_room *room, t_rlist **list);
void	print_room_links(t_rlist *list);
void	track_one_route(t_room *start);
void	malloc_paths(char ****arr, int ammount);
void	print_path(t_path *path, int i);

//algo.c
void	lemme_in(t_room *room);
void	traceroute(t_path *path, t_room *room, int *path_idx, int *room_idx);
void	path_expansion_jutsu(char ***src_arr, t_path *path, int path_amt);
void	conclude_path(t_path *path, int *path_idx, int room_idx);

//error.c
void	check_start_end_room(t_rlist *list, t_room **start);

//free.c
void	free_old_arr(char ***arr);
void	free_everything(t_rlist *list);

//quicksort.c
void	path_quicksort(t_path *path, int low, int high);

int		*max_flow_path(t_path *path, int last_path);

#endif