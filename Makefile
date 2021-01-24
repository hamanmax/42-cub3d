# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/23 10:27:39 by mhaman            #+#    #+#              #
#    Updated: 2021/01/24 12:14:04 by mhaman           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

SRC_NAME	=	move.c draw.c parsing.c parsing_map.c ray.c \
set_raycast.c set_params.c check_validity.c check_texture.c main.c \
calc_raycast.c screenshot.c

SRCS	=	$(addprefix $(SRC_PATH),$(SRC_NAME))

SRC_PATH	=	srcs/

HEADER	=	include/

OBJ_NAME	=	${SRC_NAME:.c=.o}

OBJ_PATH	=	bin/

OBJS	=	$(addprefix $(OBJ_PATH),$(OBJ_NAME))

NAME	=	Cub3D

FLAG	=	-Wall -Wextra -Werror

LIBFT	=	libft/libft.a

MINILIBX	=	minilibx-linux/libmlx_Linux.a

LIB_LINUX	=	-lXext -lX11 -lm

RM	=	rm -rf

CC	=	gcc

all: $(MINILIBX) $(LIBFT) $(OBJ_PATH) $(NAME)

$(NAME): $(OBJS) $(HEADER)
	@gcc $(FLAG) $(OBJS) $(LIBFT) $(MINILIBX) $(LIB_LINUX)  -o $(NAME)


$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	@printf "\033[2K\r\033[0;31;5;110mCompiling...	\033[37m$<\033[36m \033[0m"
	@$(CC) $(FLAG) -c $< -o $@

$(OBJ_PATH):
	mkdir -p bin/

$(LIBFT):
	@make -C libft/

$(MINILIBX):
	@make -C minilibx-linux/

clean:
	make -C libft/ clean
	$(RM) bin/

fclean:
	make -C libft/ fclean
	make -C minilibx-linux/ clean
	$(RM) bin/
	$(RM Cub3D

norme:
	make norme -C libft/
	~/./norminette-client-externe/norminette.rb srcs/

re: fclean all

.PHONY: all fclean
