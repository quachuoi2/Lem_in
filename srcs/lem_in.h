/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 06:33:58 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 13:20:29 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//MOVE THIS FILE TO INCLUDES

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libftprintf.h"
# include <stdio.h> // delet nao

# define START_ROOM		-1
# define END_ROOM		1
# define NORMAL_ROOM	0
# define UNVISITED		0
# define USED_FORWARD	1
# define BACKWARD		-1
# define UNUSED_FORWARD	0
# define MAGIC_NUMBER	30000
# define STRING_AMOUNT	100000
# define HASH_SIZE		100000
# define FOUND			1
# define NOT_FOUND		0

//error.c
# define FAIL	-1
# define OK		0

//hash.c
# define ROOM_EXIST	0
# define NEW_ROOM	1

typedef struct s_room		t_room;
typedef struct s_edge		t_edge;
typedef struct s_tracer		t_tracer;
typedef struct s_rlist		t_rlist;
typedef struct s_path		t_path;
typedef struct s_line		t_line;
typedef struct s_queue		t_queue;

struct s_room
{
	int		coord_x;
	int		coord_y;
	int		steps;
	int		ant;
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
	int	idx;
	int	steps;
};

struct s_rlist
{
	t_room	*room;
	t_rlist	*next;
};

struct s_path
{
	int		total_steps;
	int		ant_count;
	t_room	**huone;
};

struct s_line
{
	int		start;
	int		end;
	int		index;
};

struct s_queue
{
	int			remaining;
	int			count;
	int			idx;
	int			path_result;
	t_edge		*queue[MAGIC_NUMBER];
};

extern int					g_crossed;
extern int					g_ant;
extern int					g_best_path_count;
extern int					g_best_line_count;
extern t_path				*g_best_paths[MAGIC_NUMBER];
extern t_rlist				g_hash_table[HASH_SIZE];
extern t_room				*g_source;
extern t_room				*g_sink;
extern char					*g_map;

//algo.c
int		lemme_in(void);

//algo_utils.c
int		count_step(t_room *room);
int		instant_finish(void);

//quicksort.c
void	path_quicksort(t_path **path, int low, int high);

//process_map.c
void	read_map(int fd);

//process_map_utils.c
void	read_command_comments(char *str, int *start_end);
void	double_str_size(int size);
void	insurance_reading(int *ret, int fd);

//assign.c
int		assign_ants(char *line);
void	assign_room(char *line, int room_state);
void	assign_edge(char *line, int fd);

//error.c
void	check_ants_char(char c);
void	check_ant_amount(void);
void	check_empty_file(void);
void	check_empty_line(char *line);

//error_rooms.c
void	check_valid_room(char **split, t_room *room, char *line, int hsh_reslt);

//error_start_end.c
void	check_missing_start_end(void);
void	check_duplicate_start_end(t_room *room, int room_state);
void	check_start_end_reachable(int path_found);
void	check_double_command(int start_end);

//error_links.c
void	check_link_exist(int link_stage);
void	check_valid_link(t_room *r1, t_room *r2, char **split, char *line);
int		check_duplicate_link(t_room *a, t_room *b);

//hash.c
int		hash_room(t_room *room);
int		hash(char *key);
t_room	*retrieve_room(char *key);

//utilities.c
t_edge	*add_elist(t_room *from_room, t_room *to_room);
void	set_edge(t_edge *edge, t_room *from, t_room *to, int flow);
void	set_tracer(t_tracer *tracer, int idx, int steps);
void	teminate_program(void);

//bfs.c
int		bfs(t_edge *start);

//search.c
int		search(t_edge **queue, int *q_count, int idx, t_tracer *tracer);

//augment.c
int		augment(t_edge *rev_edge, int rev_i, t_room *long_room, int backward);

//augment_utils.c
void	set_flow(t_edge *list, t_room *target_room, int flow);
void	delete_forward_room(t_room *room);
void	delete_prev_room(t_room *room);
void	remove_old_longer_path(t_room *room);

//free.c
void	free_path(t_path **paths, int p_count);
void	free_room_content(t_room *room);
void	free_everything(void);

//traveler.c
void	exotic_ant_travelers(void);

//init.c
void	init_queue(t_queue *q, t_edge *start);
void	init_global(int *path_found);
void	init_conclude_path_data(int *r_i, int *bckwrd_edge_used, t_room **old);

#endif