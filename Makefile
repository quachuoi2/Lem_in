# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qnguyen <qnguyen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 06:34:08 by qnguyen           #+#    #+#              #
#    Updated: 2022/10/13 13:49:11 by qnguyen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
SRCS = main process_map process_map_utils utilities free bfs algo search \
		augment_utils augment assign quicksort traveler hash init\
		error error_rooms error_start_end error_links\
		options

SRCS_DIR = srcs/
OBJS_DIR = objs/lem_in/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRCS)))
FLAGS = -Wall -Wextra -Werror
INCLUDES = includes/
FT_PRINTF = libraries/libftprintf.a
FT_PRINTF_DIR = ft_printf/
OPTIMIZATION = -Ofast

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(OBJS) $(FT_PRINTF) -I $(INCLUDES) $(FLAGS) -o $@ $(OPTIMIZATION)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES)lem_in.h $(FT_PRINTF)
	@mkdir -p $(OBJS_DIR)
	gcc -c $(FLAGS) -I $(INCLUDES) $< -o $@ $(OPTIMIZATION)
$(FT_PRINTF):
	make -C $(FT_PRINTF_DIR)

clean:
	@make clean -C $(FT_PRINTF_DIR)
	@rm -f $(OBJS)
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C $(FT_PRINTF_DIR)
	@/bin/rm -f $(NAME)
	@/bin/rm -f a.out

re: fclean all

.PHONY: all clean fclean re