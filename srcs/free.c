/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:04:31 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/03 04:41:09 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	free_everything(t_rlist *list)
{
	t_rlist	*temp;
	t_edge	*e_temp;

	while (list)
	{
		temp = list->next;
		ft_memdel((void **)&list->room->name);
		while (list->room->edge)
		{
			e_temp = list->room->edge->next;
			ft_memdel((void **)&list->room->edge);
			list->room->edge = e_temp;
		}
		ft_memdel((void **)&list->room);
		ft_memdel((void **)&list);
		list = temp;
	}
	free_path(best_paths, best_p_count);
}