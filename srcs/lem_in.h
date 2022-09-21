/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/21 22:17:29 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libftprintf.h"
# include "get_next_line.h"
# include <stdio.h> // delet nao

# define START_ROOM -1
# define END_ROOM 1
# define NORMAL_ROOM 0
# define UNVISITED 0
# define USED_FORWARD 1
# define BACKWARD -1
# define UNUSED_FORWARD 0
# define MAGIC_NUMBER 9000

extern int	VISITED;

typedef struct s_room t_room;
typedef struct s_rlist t_rlist;
typedef struct s_path t_path;
typedef struct s_edge t_edge;
typedef struct s_elist t_elist;
typedef struct s_path_group t_path_group;

extern t_path_group best;

struct s_room
{
	int		coord_x;
	int		coord_y;
	int		state;
	int		visited;
	int		path_idx;
	int		up_for_grabz;
	char	*name;
	t_room	*prev;
	t_edge	*forward_list;
	t_rlist	*links;
};

struct s_edge
{
	int		flow;
	t_room	*from;
	t_room	*to;
	t_edge	*next;
};

struct s_rlist
{
	int		forw_list_created;
	t_room	*room;
	t_rlist	*next;
};

struct s_path
{
	int		steps;
	int		ant_count;
	t_room	*first_room; //to trace the rooms in the path via forward
};

struct s_path_group
{
	int		tol_step;
	int		path_count;
	int		line_count;
	int		*group;
};

//get.c
void	get_data(int *ants_num, int fd, t_rlist **list);
void	get_rooms(t_rlist **list, int fd);
void	get_links(t_rlist *list, char *line, int fd);

//error.c
void	check_start_end_room(t_rlist *list, t_room **start);
void	check_ants(char *line);

//free.c
void	free_old_arr(char ***arr);
void	free_everything(t_rlist *list);

//utilities.c
void	add_room_list(t_room *room, t_rlist **list);
t_edge	*add_elist(t_room *from_room, t_room *to_room);
t_edge	*new_edge(t_room *cur_room, t_room *to_room);
void	edge_assign(t_edge *edge, t_room *from, t_room *to, int flow);

//bfs.c
int	bfs(t_edge *start, int ant);

//algo.c
void	line_count(t_path_group *cur, t_path *path, int max_ant);
//void	lemme_in(t_room *room, t_path *path, int ant_num);

//path_utilities.c
void	init_path_groups(t_path_group *group);
void	adjust_path_group(t_path_group *cur, t_path *path, int *path_idx);
void	assign_best_group(t_path_group *best, t_path_group *cur);
int		conclude_path(t_edge *rev_queue, int revq_idx, t_path *path, int path_idx);

//search.c
int		search_free_link(t_edge **queue, int *q_count, int idx);
int		search_forward(t_edge **queue, int *q_count, int idx);
int		search_backward(t_edge **queue, int *q_count, int idx);

#endif