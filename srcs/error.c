/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:29:54 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/13 16:03:56 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	check_ants_char(char c)
{
	if (!ft_isdigit(c))
	{
		ft_printf("ERROR: What kind of ant is this???\n");
		teminate_program();
	}
}

void	check_ant_amount(void)
{
	if (g_ant < 1)
	{
		ft_printf("ERROR: Bad ant amount\n");
		teminate_program();
	}
}

void	check_empty_file(void)
{
	if (g_map[0] == 0)
	{
		ft_printf("ERROR: You need a map if you want this to work sir\n");
		teminate_program();
	}
}

void	check_empty_line(char *line)
{
	if (line[0] == '\n' || line[0] == 0 || line[0] == 'L')
	{
		ft_printf("ERROR: Bad line\n");
		teminate_program();
	}
}

void	check_malloc(void *mem)
{
	if (mem == NULL)
	{
		ft_printf("ERROR: Failed to allocate memory\n");
		teminate_program();
	}
}
