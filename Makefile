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
	@printf "\n\033[1m\033[32mCub3D Compilation done\n\033[32m\033[1m"


$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER)
	@printf "\033[2K\r\033[0;31;5;110mCompiling...	\033[37m$<\033[36m \033[0m"
	@$(CC) $(FLAG) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p bin/

$(LIBFT):
	@printf "\033[1m\033[32mLibft Compilation done\n\033[32m\033[1m"
	@make -s -C libft/ > /dev/null

$(MINILIBX):
	@printf "\033[1m\033[32mMinilibx Compilation done\n\033[32m\033[1m"
	@make -s -C minilibx-linux/ > /dev/null 2>&1
clean:
	@printf "\033[1m\033[32mObj files deleted succesfuly\n\033[32m\033[1m"
	@make -C libft/ clean > /dev/null
	@$(RM) bin/
	@make -s -C minilibx-linux/ clean > /dev/null

fclean:
	@printf "\033[1m\033[32mObj files and binary deleted succesfuly\n\033[32m\033[1m"
	@make -s -C libft/ fclean
	@make -s -C minilibx-linux/ clean > /dev/null
	@$(RM) bin/
	@$(RM) Cub3D
	@$(RM) minilibx-linux/libxmlx_linux.a

re: fclean all

.PHONY: all fclean re clean
