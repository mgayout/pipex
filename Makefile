# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 12:39:21 by mgayout           #+#    #+#              #
#    Updated: 2024/03/13 17:38:19 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wextra -Wall -Werror -g3
REMOVE	=	rm -f
SRC_DIR	=	./src/
SRC_B	=	./src/bonus/
LIBFT	=	./libft-/libft.a

SRC		=	src/main.c \
			src/init_pipex.c \
			src/children.c \
			src/free.c \

SRC_B	=	src/bonus/main_bonus.c \
			src/bonus/init_pipex_bonus.c \
			src/bonus/children_bonus.c \
			src/bonus/free_bonus.c \

ifndef WITH_BONUS
SRCS			=	$(SRC)
else
SRCS			=	$(SRC_B)
endif

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT)
			$(CC) $(SRCS) $(LIBFT) $(CFLAGS) -o $(NAME)
			
bonus:
			@make WITH_BONUS=1 all

$(LIBFT):
			@make -C libft-/

clean:	
			@make clean -C libft-/

fclean:		clean
			$(REMOVE) $(NAME)
			$(REMOVE) $(LIBFT)

re: fclean all

rebonus: fclean ${NAME}

.PHONY: all clean fclean re bonus rebonus