/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 09:08:02 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/04 11:42:22 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	set_hash(t_rlist *slot, t_room *room)
{
	slot->room = room;
	slot->next = NULL;
	return (1);
}

unsigned int hash(char *key)
{
	int	value;
	int key_length;
	int	i;

	key_length = ft_strlen(key);
	i = 0;
	value = 0;
	while (i < key_length)
	{
		value = value * 42 + key[i];
		i++;
	}
	value = value % HASH_SIZE;
	return (value);
}

int	hash_room(t_room *room)
{
	int		idx;
	t_rlist	*new_collision;
	t_rlist	*temp;

	idx = hash(room->name);
	if (hash_table[idx].room == NULL)
		return (set_hash(&hash_table[idx], room));
	temp = &hash_table[idx];
	while (temp != NULL)
	{
		if (ft_strcmp(temp->room->name, room->name) == 0)
			return (0);
		new_collision = temp;
		temp = temp->next;
	}
	new_collision = ft_memalloc(sizeof(t_rlist));
	return (set_hash(new_collision, room));
}