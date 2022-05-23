# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 06:34:08 by qnguyen           #+#    #+#              #
#    Updated: 2022/05/23 09:16:36 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS = main.c error.c get.c rlist.c
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/

all: $(NAME)

$(NAME):
	gcc -g $(SRCS) -L . -lftprintf $(INCLUDES)

clean:
	@/bin/rm -f $(wildcard *.o)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
