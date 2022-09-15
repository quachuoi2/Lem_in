/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:28:33 by qnguyen           #+#    #+#             */
/*   Updated: 2022/06/14 06:15:35 by qnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define FD_SIZE 4096
# define BUFF_SIZE 42
# define ERROR_READ -1
# define DONE_READ 0
# define LINE_READ 1
# include "libft.h"

int	get_next_line(const int fd, char **line);

#endif