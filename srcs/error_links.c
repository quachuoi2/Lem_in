/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:58:04 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 12:55:36 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_link_exist(int link_stage)
{
	if (link_stage == 0)
	{
		ft_printf("ERROR: No links found\n");
		teminate_program();
	}
}

static int	check_multiple_dashes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '-' && line[i + 1] == '-')
		{
			ft_printf("ERROR: Multiple dashes in link\n");
			return (FAIL);
		}
		i++;
	}
	return (OK);
}

void	check_valid_link(t_room *r1, t_room *r2, char **split, char *line)
{
	if (!r1 || !r2 || check_multiple_dashes(line) == FAIL)
	{
		ft_printf("ERROR: Invalid line found\n");
		ft_arrdel(&split);
		teminate_program();
	}
}

int	check_duplicate_link(t_room *a, t_room *b)
{
	int		duplicate;
	t_edge	*temp;

	duplicate = NOT_FOUND;
	temp = a->edge;
	while (temp)
	{
		if (ft_strcmp(temp->to->name, b->name) == 0)
			duplicate = FOUND;
		temp = temp->next;
	}
	return (duplicate);
}
