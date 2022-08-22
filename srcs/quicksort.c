/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:16:56 by qnguyen           #+#    #+#             */
/*   Updated: 2022/08/16 15:46:39 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	path_swap(t_path *a, t_path *b)
{
	t_path	ptr;

	ptr = *a;
	*a = *b;
	*b = ptr;
}

int	partition(t_path *path, int low, int high)
{
	int	pivot;
	int	i;
	int	index;

	pivot = path[high].steps;
	i = low;
	index = low;
	while (i < high)
	{
		if (path[i].steps < pivot)
		{
			path_swap(&path[i], &path[index]);
			index++;
		}
		i++;
	}
	path_swap(&path[index], &path[high]);
	return (index);
}

void	path_quicksort(t_path *path, int low, int high)
{
	int	partition_index;

	if (low < high)
	{
		partition_index = partition(path, low, high);
		path_quicksort(path, low, partition_index - 1);
		path_quicksort(path, partition_index + 1, high);
	}
}
