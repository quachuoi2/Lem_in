/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/03 04:18:21 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libftprintf.h"
# include "get_next_line.h"
# include <stdio.h> // delet nao

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

# define START_ROOM -1
# define END_ROOM 1
# define NORMAL_ROOM 0
# define UNVISITED 0
# define USED_FORWARD 1
# define BACKWARD -1
# define UNUSED_FORWARD 0
# define MAGIC_NUMBER 30000

extern int	CROSSED;

typedef struct s_room t_room;
typedef struct s_rlist t_rlist;
typedef struct s_path t_path;
typedef struct s_edge t_edge;
typedef struct s_elist t_elist;
typedef struct s_edge_idx t_edge_idx ;
typedef struct s_tracer t_tracer;

struct s_room
{
	int		coord_x;
	int		coord_y;
	int		state;
	int		step_count;
	char	*name;
	t_room	*prev;
	t_room	*next;
	t_edge	*edge;
};

struct s_edge
{
	int		crossed;
	int		flow;
	t_room	*from;
	t_room	*to;
	t_edge	*next;
};

struct s_tracer
{
	int idx;
	int step_count;
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
	t_room	**huone; //to trace the rooms in the path via forward
};

//algo.c
int		lemme_in(t_room *start, t_path **best_paths, int *best_line_count, int *best_p_count, int ant);

//assign.c
void	assign_room(t_room **room, char *line);
void	assign_start_end_room(t_room **room, char **line, int fd);
void	assign_edge(t_room *a, t_room *b);

//get.c
void	get_data(int *ants_num, int fd, t_rlist **list);
void	get_rooms(t_rlist **list, int fd);
void	get_links(t_rlist *list, char *line, int fd);

//error.c
void	check_start_end_room(t_rlist *list, t_room **start);
void	check_ants(char *line);

//free.c
void	free_path(t_path **paths, int p_count);
void	free_everything(t_rlist *list, t_path **best_paths, int p_count);

//utilities.c
void	add_room_list(t_room *room, t_rlist **list);
t_edge	*add_elist(t_room *from_room, t_room *to_room);
void	set_edge(t_edge *edge, t_room *from, t_room *to, int flow);

//bfs.c
int		bfs(t_edge *start);

//augment.c
void	mixed_augment(t_edge *rev_edge, int rev_count);
void	pure_forward_augment(t_edge *rev_edge, int rev_count);

//path_utilities.c

//search.c
int		search_forward(t_edge **queue, int *q_count, int idx, t_tracer *tracer);

//edmond_karp_utils.c
void	set_flow(t_edge *list, t_room *target_room, int flow);
void	delete_forward_room(t_room *room);
void	delete_prev_room(t_room *room);
void	remove_old_longer_path(t_room *room);

//quicksort.c
void	path_quicksort(t_path **path, int low, int high);

#endif