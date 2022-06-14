# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 06:34:08 by qnguyen           #+#    #+#              #
#    Updated: 2022/06/13 19:50:20 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
SRCS = main.c error.c get.c rlist.c utilities.c algo.c
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
