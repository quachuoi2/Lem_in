/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:58:04 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 15:58:30 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

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

static int	check_empty_room(t_room *r1, t_room *r2)
{
	if (!r1 || !r2)
	{
		ft_printf("ERROR: Invalid line found\n");
		return (FAIL);
	}
	return (OK);
}

static int	check_duplicate_link(t_room *a, t_room *b)
{
	t_edge	*temp;

	temp = a->edge;
	while (temp)
	{
		if (ft_strcmp(temp->to->name, b->name) == 0)
		{
			ft_printf("ERROR: Duplicate links found\n");
			return (FAIL);
		}
		temp = temp->next;
	}
	return (OK);
}

void	check_valid_link(t_room *r1, t_room *r2, char **split, char *line)
{
	if (check_empty_room(r1, r2) == FAIL
		|| check_multiple_dashes(line) == FAIL
		|| check_duplicate_link(r1, r2) == FAIL)
	{
		ft_arrdel(&split);
		teminate_program();
	}
}
