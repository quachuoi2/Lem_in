# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 06:34:08 by qnguyen           #+#    #+#              #
#    Updated: 2022/08/29 18:08:24 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
SRCS = main.c error.c get.c utilities.c algo.c free.c quicksort.c \
		ford_fulkerson.c traveler.c
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/

all: $(NAME)

$(NAME):
	gcc -g $(addprefix srcs/, $(SRCS)) -L . -lftprintf $(INCLUDES)

clean:
	@/bin/rm -f $(wildcard *.o)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out
re: fclean all
