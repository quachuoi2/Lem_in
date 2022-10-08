/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:53:31 by qnguyen           #+#    #+#             */
/*   Updated: 2022/10/08 12:56:33 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_room_input(char **split, t_room *room)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		ft_printf("ERROR: Invalid line\n");
		return (FAIL);
	}
	return (OK);
}

static int	check_room_coordinates(char **split, t_room *room)
{
	int	i;
	int	room_status;

	i = 0;
	room_status = OK;
	while (split[1][i])
		if (ft_isdigit(split[1][i++]) == 0)
			room_status = FAIL;
	i = 0;
	while (split[2][i])
		if (ft_isdigit(split[2][i++]) == 0)
			room_status = FAIL;
	if (room_status == FAIL)
		ft_printf("ERROR: Invalid line\n");
	return (room_status);
}

static int	check_duplicate_room(int hash_result, char **split, t_room *room)
{
	if (hash_result == ROOM_EXIST)
	{
		ft_printf("ERROR: Duplicate rooms found\n");
		free_room_content(room);
		return (FAIL);
	}
	return (OK);
}

static int	check_multiple_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' && line[i + 1] == ' ')
		{
			ft_printf("ERROR: Invalid line\n");
			return (FAIL);
		}
		i++;
	}
	return (OK);
}

void	check_valid_room(char **split, t_room *room, char *line, int hsh_result)
{
	if (check_room_input(split, room) != OK
		|| check_room_coordinates(split, room) != OK
		|| check_duplicate_room(hsh_result, split, room) != OK
		|| check_multiple_spaces(line) != OK)
	{
		ft_arrdel(&split);
		teminate_program();
	}
}