/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:04:31 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/16 09:12:14 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* void	free_old_arr(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (i < NUM_OF_PATH)
	{
		j = 0;
		while (j < NUM_OF_ROOM_PER_PATH)
		{
			ft_memdel((void **)&arr[i][j]);
			j++;
		}
		ft_memdel((void **)&arr[i]);
		i++;
	}
} */

void	free_everything(t_rlist *list)
{
	t_rlist	*temp;
	t_rlist	*temp2;

	while (list)
	{
		temp = list->next;
		free(list->room->name);
		while (list->room->links)
		{
			temp2 = list->room->links->next;
			free(list->room->links);
			list->room->links = temp2;
		}
		free(list->room);
		free(list);
		list = temp;
	}
}
