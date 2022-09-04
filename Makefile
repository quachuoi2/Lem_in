# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 06:34:08 by qnguyen           #+#    #+#              #
#    Updated: 2022/09/04 03:16:33 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem_in
SRCS = main.c error.c get.c utilities.c algo.c free.c quicksort.c \
		flow.c traveler.c path_utilities.c trash_algo.c
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/
LIB = -L ./lib -lftprintf

all: $(NAME)

$(NAME):
	gcc -g $(addprefix srcs/, $(SRCS)) $(LIB) $(INCLUDES)

clean:
	@/bin/rm -f $(wildcard *.o)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out

re: fclean all
