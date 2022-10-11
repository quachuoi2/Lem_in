/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:28:21 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/11 17:19:56 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	print_help(void)
{
	ft_printf("lem-in - the ant distributor\n");
	ft_printf("SYNOPSIS\n");
	ft_printf("\t./lem-in [-h] [-l] [-q] [-nomap] [-nodistribution] < 'map'\n");
	ft_printf("OPTIONS\n");
	ft_printf("\t-h\n\t\tPrints the synopsis and a list of commands\n");
	ft_printf("\t-l\n\t\tPrints the ant's traversal line count at the end\n");
	ft_printf("\t-nomap\n\t\tDisable printing the map\n");
	ft_printf("\t-nodistribution\n\t\tDisable printing the ants distribution\n");
	ft_printf("\t-q\n\t\tDisable both map and ant distribution printing\n");
	free(g_map);
	exit (0);
}

void	handle_options(t_flags *flags)
{
	if (flags->nomap == 0)
		ft_printf("%s\n", g_map);
	if (flags->nodistribution == 0)
		exotic_ant_travelers();
	if (flags->line == 1)
		ft_printf("%d\n", g_best_line_count);
}

void	check_options(int argc, char **argv, t_flags *flags)
{
	int	i;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			if (flags->line == 0 && ft_strcmp(argv[i], "-l") == 0)
				flags->line = 1;
			else if (ft_strcmp(argv[i], "-nomap") == 0)
				flags->nomap = 1;
			else if (ft_strcmp(argv[i], "-nodistribution") == 0)
				flags->nodistribution = 1;
			else if (ft_strcmp(argv[i], "-q") == 0)
			{
				flags->nomap = 1;
				flags->nodistribution = 1;
			}
			else if (ft_strcmp(argv[i], "-h") == 0)
				print_help();
			i++;
		}
	}
}
