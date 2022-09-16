/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/09/16 15:30:47 by qnguyen          ###   ########.fr       */
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
# define MAGIC_NUMBER 3000

typedef struct s_room t_room;
typedef struct s_rlist t_rlist;
typedef struct s_path t_path;
typedef struct s_edge t_edge;
typedef struct s_path_group t_path_group;

extern int	g_final_idx;

struct s_room
{
	int		coord_x;
	int		coord_y;
	int		state;
	int		occupied;
	int		path_idx;
	char	*name;
	t_edge	*forward;
	t_edge	*backward;
	t_rlist	*links;
};

struct s_edge
{
	int		crossed;
	int		flow;
	t_room	*from;	//normally, edge.from is the current room, edge.to is the next room
	t_room	*to;
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

//bfs.c
void	bfs(t_room *room, int ant);
void	conclude_path(t_edge *queue, int q_idx, t_path *path, int path_idx);

//algo.c
void	line_count(t_path_group *cur, t_path *path, int max_ant);
//void	lemme_in(t_room *room, t_path *path, int ant_num);

//path_utilities.c
void	init_path_groups(t_path_group *group);
void	adjust_path_group(t_path_group *cur, t_path *path, int *path_idx);
void	assign_best_group(t_path_group *best, t_path_group *cur);
void	assign_rev_queue(t_edge *rev, t_edge *queue);

#endif