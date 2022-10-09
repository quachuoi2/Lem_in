/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 07:04:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/09 14:52:59 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	read_command_comments(char *str, int *start_end)
{
	check_double_command_comment(*start_end);
	if (!ft_strcmp(str, "##start"))
		*start_end = START_ROOM;
	else if (!ft_strcmp(str, "##end"))
		*start_end = END_ROOM;
}

void	double_str_size(int size)
{
	char	*insurance_str;

	insurance_str = ft_memalloc(sizeof(char) * (size * 2));
	ft_memcpy(insurance_str, g_map, size);
	ft_memdel((void **)&g_map);
	g_map = insurance_str;
}

void	insurance_reading(int *ret, int fd)
{
	int	total;

	if (*ret < STRING_AMOUNT)
		return ;
	total = *ret;
	while (*ret > 0)
	{
		double_str_size(total);
		*ret = read(fd, &g_map[total], total);
		total += *ret;
	}
	*ret = total;
}
