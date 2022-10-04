/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 07:04:51 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/04 08:45:21 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	get_command(char *str)
{
	int	start_end;

	start_end = NORMAL_ROOM;
	if (!ft_strcmp(str, "##start"))
		start_end = START_ROOM;
	else if (!ft_strcmp(str, "##end"))
		start_end = END_ROOM;
	return (start_end);
}

void	double_str_size(char **str, int size)
{
	char *insurance_str;

	insurance_str = ft_memalloc(sizeof(char) * (size * 2));
	ft_memcpy(insurance_str, *str, size);
	ft_memdel((void **)str);
	*str = insurance_str;
}

int	insurance_reading(char **str, int ret, int fd)
{
	int	total;

	total = ret;
	while (ret)
	{
		double_str_size(str, total);
		ret = read(fd, &(*str)[total], total - 1);
		total += ret;
	}
	return (total);
}
