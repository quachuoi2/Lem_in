/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/04 03:17:18 by qnguyen          ###   ########.fr       */
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
# define NUM_OF_PATH 1000
# define NUM_OF_ROOM_PER_PATH 1000

typedef struct s_room t_room;
typedef struct s_rlist t_rlist;
typedef struct s_path t_path;

extern int	g_final_idx;
struct s_room
{
	int		coord_x;
	int		coord_y;
	int		ant;
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
	int		ant_count;
	t_room	**room;
};

//get.c
void	get_data(int *ants_num, int fd, t_rlist **list);
void	get_rooms(t_rlist **list, int fd);
void	get_links(t_rlist *list, char *line, int fd);

//utilities.c
void	add_room_list(t_room *room, t_rlist **list);
void	initialize_paths(t_path **path);
void	initialize_best_path(int **best_path);
void	malloc_paths(char ****arr, int ammount);
//deletable
void	print_room_links(t_rlist *list);
void	print_path(t_path *path);
void	print_flow_path(t_path *path, int *flow_path, int mof);
void	print_path_ant_count(t_path *path, int *best_path);

//algo.c
void	lemme_in(t_room *room, t_path *path, int ant_num);
void	traceroute(t_path *path, t_room *room, int *room_idx);
void	conclude_path(t_path *path, int room_idx);

//error.c
void	check_start_end_room(t_rlist *list, t_room **start);
void	check_ants(char *line);

//free.c
void	free_old_arr(char ***arr);
void	free_everything(t_rlist *list);

//quicksort.c
void	path_quicksort(t_path *path, int low, int high);

//flow.c
void	max_flow_path(t_path *path, int *max_flow_group, int target_flow, int iter);
int		target_flow_count(t_path *path, int *best_path, int max_ant);

//path_utilities.c
int		path_room_count(t_path *path, int *path_idx, int flow);
int		check_path(t_path *path, int path_idx);
void	retrace_rooms(t_path *cur_path, int reached_room);
void	retrace_all_path(t_path *path, int *temp_path, int flow);
void	assign_path(int *dest_path, int *src_path, int flow);
//void	path_expansion_jutsu(char ***src_arr, t_path *path, int path_amt);

//ant_traveler.c
int		instant_finish(t_path *path, int max_ant);
int		exotic_ant_traveler(t_path *path, int *best_path, int ant_num, int target_flow);
void	ant_distributor(t_path *path, int *best_path, int max_ant);


int	do_the_thingy(t_path *path, int *btg, int target_flow);

#endif