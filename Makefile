# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 06:34:08 by qnguyen           #+#    #+#              #
#    Updated: 2022/10/04 09:08:12 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = a.out
#change name
#change name
FILE = main error get utilities free bfs algo search augment_utils augment \
		assign quicksort algo_utils traveler get_utils hash
SRCS = srcs/
O_DIR = objs/
FLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes/
LIB = -L ./lib -lftprintf
OPTIMIZATION = -Ofast

all: $(NAME)

$(NAME): $(addprefix $(O_DIR), $(addsuffix .o, $(FILE)))
	gcc $^ $(LIB) $(INCLUDES) #-o $(NAME)

$(O_DIR)%.o: $(SRCS)%.c $(SRCS)lem_in.h
	@mkdir -p $(O_DIR)
	gcc -c $< $(LIB) $(INCLUDES) -o $@ -g

clean:
	@rm -rf $(O_DIR)
	@rm -f $(wildcard *.o)

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out

re: fclean all

.PHONY: all clean fclean re