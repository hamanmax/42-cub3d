# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaman <mhaman@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/25 08:58:00 by mhaman            #+#    #+#              #
#    Updated: 2021/01/21 14:28:45 by mhaman           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


SRC_STR		=	$(addprefix str/,ft_split.c  ft_strchr.c  ft_strfdup.c ft_str_isdigit.c  ft_strlcat.c  ft_strlen.c  ft_strmapi.c  ft_strnstr.c  ft_strsep.c  ft_subfstr.c\
				ft_str_char_occur.c  ft_strdup.c  ft_strfjoin.c  ft_strjoin.c ft_strlcpy.c  ft_str_malloc.c  ft_strncmp.c  ft_strrchr.c  ft_strtrim.c  ft_substr.c)

SRC_MEM		=	$(addprefix mem/,ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_calloc.c ft_bzero.c)

SRC_CHAR	=	$(addprefix char/, ft_isalnum.c  ft_isalpha.c  ft_isascii.c  ft_isdigit.c  ft_isprint.c  ft_isspace.c  ft_tolower.c  ft_toupper.c)

SRC_PRINTF	=	$(addprefix printf/, apply_cu_flags.c  apply_d_flags.c  apply_s_option.c  apply_x_flags.c  check_zero_flag.c  ft_printf.c  ft_split_printf.c  parse_diux_option.c  parsing_line.c)

SRC_MATH	=	$(addprefix math/,ft_atoi.c  ft_itoa_base.c  ft_itoa_base_long.c  ft_itoa.c  ft_itoa_unsigned.c  ft_pow.c  ft_round.c)

SRC_WRITE	=	$(addprefix write/, ft_putchar_fd.c  ft_putendl_fd.c  ft_putnbr_fd.c  ft_putstr_fd.c  get_next_line.c)

SRCS_NAME	=	$(SRC_CHAR) $(SRC_MATH) $(SRC_MEM) $(SRC_PRINTF) $(SRC_STR) $(SRC_WRITE)

HEADER		=	include/

SRC_PATH	=	srcs/

SRCS		=	$(addprefix $(SRC_PATH), $(SRCS_NAME))
 
OBJ_NAME	=	${SRC_NAME:.c=.o}

OBJ_PATH	=	bin/

OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))

SRC_PATH	=	srcs/

SRCS		=	$(addprefix $(SRC_PATH), $(SRCS_NAME))

OBJ_NAME	=	${SRCS_NAME:.c=.o}

OBJ_PATH	=	bin/

OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))



DEBUG_FLAGS ?=

NAME = libft.a

FLAG	=	-Wall -Wextra -g3 -D BUFFER_SIZE=100

RM = rm -rf

CC = cc

all: $(OBJ_PATH) $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@ar rcs $(NAME) $(OBJ)
	@printf "	\033[2K\r\033[1;38;5;110mlibft\t:\t\033[0;38;5;121mUpdated\n\033[0m"

$(OBJ_PATH):
	@mkdir -p bin/ 2> /dev/null
	@mkdir -p bin/math 2> /dev/null
	@mkdir -p bin/char 2> /dev/null
	@mkdir -p bin/printf 2> /dev/null
	@mkdir -p bin/mem 2> /dev/null
	@mkdir -p bin/str 2> /dev/null
	@mkdir -p bin/write 2> /dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(HEADER) Makefile
	@printf "\033[2K\r\033[0;31;5;110mCompiling...	\033[37m$<\033[36m \033[0m"
	@gcc $(FLAG) -g3 -I ${HEADER} -c $< -o $@


clean:
	@${RM} ${OBJ_PATH}

fclean: clean
	@${RM} ${NAME}

re: fclean all

debug:
	make all DEBUG_FLAGS="-g3 -fsanitize=address"

redebug:
	make re DEBUG_FLAGS="-g3 -fsanitize=address"

.PHONY: all clean fclean re debug redebug