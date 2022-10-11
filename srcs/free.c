/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:04:31 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 15:58:43 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	free_path(t_path **paths, int p_count)
{
	int	i;

	i = 0;
	while (i < p_count)
	{
		ft_memdel((void **)&paths[i]->huone);
		ft_memdel((void **)&paths[i]);
		i++;
	}
}

void	free_room_content(t_room *room)
{
	t_edge	*edge;

	ft_memdel((void **)&room->name);
	while (room->edge)
	{
		edge = room->edge->next;
		ft_memdel((void **)&room->edge);
		room->edge = edge;
	}
	free(room);
}

static void	free_hash_rooms(t_rlist *hash_slot)
{
	int		collision_count;
	t_rlist	*temp;

	collision_count = 0;
	while (hash_slot)
	{
		temp = hash_slot->next;
		free_room_content(hash_slot->room);
		hash_slot->room = NULL;
		if (collision_count > 0)
			ft_memdel((void **)&hash_slot);
		hash_slot = temp;
		collision_count++;
	}
}

static void	free_all_rooms(void)
{
	int	i;

	i = 0;
	while (i < HASH_SIZE)
	{
		if (g_hash_table[i].room)
			free_hash_rooms(&g_hash_table[i]);
		i++;
	}
}

void	free_everything(void)
{
	free_all_rooms();
	if (g_map)
		ft_memdel((void **)&g_map);
	free_path(g_best_paths, g_best_path_count);
}
