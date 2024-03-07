# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgayout <mgayout@student.42nice.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/05 12:39:21 by mgayout           #+#    #+#              #
#    Updated: 2024/03/07 14:23:55 by mgayout          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
NAME_B	= 	pipex_bonus
CC		=	gcc
CFLAGS	=	-Wextra -Wall -Werror -g3
REMOVE	=	rm -f
SRC_DIR	=	./src/
SRC_B	=	./src/bonus/
LIBFT	=	./libft-/libft.a

SRCS	=	src/main.c \
			src/init_pipex.c \
			src/children_parent.c \

SRCS_B	=	src/bonus/main_bonus.c \
			src/bonus/init_pipex_bonus.c \
			src/bonus/children_parent_bonus.c \

all: $(LIBFT) $(NAME)

$(NAME): $(LIBFT)
			$(CC) $(SRCS) $(LIBFT) $(CFLAGS) -o $(NAME)
			
bonus: $(LIBFT) $(NAME_B)

$(NAME_B): $(LIBFT)
			$(CC) $(SRCS_B) $(LIBFT) $(CFLAGS) -o $(NAME_B)

$(LIBFT):
			@make -C libft-/

clean:	
			@make clean -C libft-/

fclean:		clean
			$(REMOVE) $(NAME)
			$(REMOVE) $(NAME_B)
			$(REMOVE) $(LIBFT)

re: fclean all

rebonus: fclean ${NAME_B}

.PHONY: all clean fclean re bonus rebonus