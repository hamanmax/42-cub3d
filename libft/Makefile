# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhaman <mhaman@student.le-101.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/25 08:58:00 by mhaman            #+#    #+#              #
#    Updated: 2020/03/04 10:39:51 by mhaman           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #


SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isspace.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_itoa_unsigned.c \
											ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_itoa_base.c ft_itoa_base_long.c\
											ft_strfjoin.c ft_subfstr.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
											ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_strfdup.c ft_strsep.c get_next_line.c

OBJ = $(SRC:.c=.o)

WFLAGS = -Wall -Wextra -Werror

DEBUG_FLAGS ?=

NAME = libft.a

RM = rm -f

all: $(NAME)

$(NAME):	$(OBJ)
	ar -rc $@ $^ 

%.o: %.c libft.h
	$(CC) $(WFLAGS) $(DEBUG_FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:
	make fclean
	make all

debug:
	make all DEBUG_FLAGS="-g3 -fsanitize=address"

redebug:
	make re DEBUG_FLAGS="-g3 -fsanitize=address"

.PHONY: all clean fclean re debug redebug