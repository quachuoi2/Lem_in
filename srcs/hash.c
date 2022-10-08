/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:08:02 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 12:48:21 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	set_new_hash_slot(t_rlist *slot, t_room *room)
{
	slot->room = room;
	slot->next = NULL;
	return (NEW_ROOM);
}

int	hash_value(char *key)
{
	int	value;
	int	i;

	i = 0;
	value = 0;
	while (key[i])
	{
		value = value * 42 + key[i];
		i++;
	}
	value = value % HASH_SIZE;
	return (value);
}

int	check_exisiting_hash_slot(t_rlist **last_slot, char *room_name)
{
	t_rlist	*new_collision;

	new_collision = *last_slot;
	while (new_collision != NULL)
	{
		if (ft_strcmp(new_collision->room->name, room_name) == 0)
			return (ROOM_EXIST);
		*last_slot = new_collision;
		new_collision = new_collision->next;
	}
	return (NEW_ROOM);
}

int	hash_room(t_room *room)
{
	int		idx;
	t_rlist	*last_slot;

	idx = hash_value(room->name);
	if (g_hash_table[idx].room == NULL)
		return (set_new_hash_slot(&g_hash_table[idx], room));
	last_slot = &g_hash_table[idx];
	if (check_exisiting_hash_slot(&last_slot, room->name) == ROOM_EXIST)
		return (ROOM_EXIST);
	last_slot->next = ft_memalloc(sizeof(t_rlist));
	return (set_new_hash_slot(last_slot->next, room));
}

t_room	*retrieve_room(char *key)
{
	t_rlist	*temp;

	if (key)
	{
		temp = &g_hash_table[hash_value(key)];
		while (temp->room && ft_strcmp(temp->room->name, key) != 0)
			temp = temp->next;
		if (temp)
			return (temp->room);
	}
	return (NULL);
}
