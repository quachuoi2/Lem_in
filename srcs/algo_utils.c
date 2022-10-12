/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:23:53 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/12 16:37:02 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int	count_step(t_room *room)
{
	int	i;

	i = 1;
	while (room != g_sink)
	{
		room->steps = i++;
		room = room->next;
	}
	return (i);
}

int	instant_finish(void)
{
	int			i;
	int			j;
	t_ant_distr	distr;

	i = 0;
	while (i < g_best_path_count)
	{
		if (g_best_paths[i]->huone[0] == g_sink)
		{
			init_ant_distr(&distr);
			j = 0;
			while (j <= g_ant)
				insert_ant(&distr, g_best_paths[i]->huone[0]->name, j++);
			ft_putendl(distr.line);
			ft_memdel((void **)&distr.line);
			free_everything();
			exit (0);
		}
		i++;
	}
	return (-1);
}
